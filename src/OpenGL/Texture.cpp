#include <OpenGL/Texture.h>
#include <Threading/Dispatcher.h>
#include <Security/Cryptography.h>
#include <Application/App.h>

// STB Image performance optimizations
#define STBI_NO_FAILURE_STRINGS  // Disable error strings for performance
#define STB_IMAGE_IMPLEMENTATION
#include <OpenGL/stb_image.h>

namespace xit::OpenGL
{
    std::map<std::string, Texture> Texture::textures;
    std::list<std::string> Texture::failedImages;
    int Texture::textureMaxSize = 0;

    GLuint Texture::TextureName()
    {
        return textureId;
    }

    GLuint Texture::GetChannels() const
    {
        return numberOfChannels;
    }

    void Texture::Bind() const
    {
        //	Bind our texture object (make it the current texture).
        glBindTexture(GL_TEXTURE_2D, textureId);
    }

    void Texture::Unbind() const
    {
        //	Bind our texture object (make it the current texture).
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    bool Texture::Create()
    {
        //  If the texture currently exists in OpenGL, destroy it.
        Destroy();

        //  Generate and store a texture identifier.
        glGenTextures(1, &textureId);

        return true;
    }

    bool Texture::Create(unsigned char *data, int width, int height, int nrChannels)
    {
        if (textureMaxSize == 0)
        {
            // store only once in static variable
            glGetIntegerv(GL_MAX_TEXTURE_SIZE, &textureMaxSize);
        }

        //	Set the width and height.
        this->width = width;
        this->height = height;

        //  Create the underlying OpenGL object.
        Create();
        Bind();

        GLint format = nrChannels == 1 ? GL_RED : nrChannels == 3 ? GL_RGB
                                                                  : GL_RGBA;

        numberOfChannels = nrChannels;

        //  Set the image data.
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);

        //  Set linear filtering mode.
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        //  We're done!
        return true;
    }

    bool Texture::Create(const std::string &path, int width, int height)
    {
        //  Store path for async loading and dispatch entire loading process to background thread
        try
        {
            this->filePath = path;
            
            // Dispatch entire loading process to background thread
            Dispatcher::Invoke(std::bind(&Texture::CreateFromFileAsync, this));
            
            return true; // Optimistic return, check done flag later
        }
        catch (...)
        {
            // Couldn't initiate async loading
            return false;
        }
    }

    void Texture::Destroy()
    {
        //  Only destroy if we have a valid id.
        if (textureId != 0)
        {
            //	Delete the texture object.
            glDeleteTextures(1, &textureId);
            textureId = 0;

            //  Destroy the pixel data.
            pixelData = nullptr;

            //  Reset width and height.
            width = height = 0;
        }
    }

    const Texture *Texture::FindOrCreateTexture(const std::string &file, int width, int height)
    {
        static std::mutex texturesMutex;
        std::unique_lock<std::mutex> lock(texturesMutex);

        // Check if the texture already exists.
        auto it = textures.find(file);
        if (it != textures.end())
        {
            return &it->second;
        }

        // Create a new texture entry in the map and keep the lock
        Texture &texture = textures[file];
        
        // Create the texture while holding the lock to prevent race conditions
        texture.Create(file, width, height);
        
        return &texture;
    }

    void Texture::CreateAsync()
    {
        try
        {
            created = Create(pixelData, width, height, numberOfChannels);
            done = true;    
        }
        catch(const std::exception& e)
        {
            std::cerr << "Fuck: " << e.what() << '\n';
        }

        stbi_image_free(pixelData);
        pixelData = nullptr;
    }

    void Texture::CreateFromFileAsync()
    {
        try
        {
            std::string fileName = filePath; // TODO File::Find(filePath);
            
            if (!fileName.empty())
            {
                int imageWidth, imageHeight, nrChannels;
                
                // Optimize: Load directly from file instead of loading to memory first
                if (fileName.ends_with(".enc"))
                {
                    // For encrypted files, we still need to decrypt first
                    std::vector<char> bytes = Security::Cryptography::DecryptFromFile(fileName, App::GetPassword());
                    pixelData = stbi_load_from_memory((unsigned char *)bytes.data(), static_cast<int>(bytes.size()), &imageWidth, &imageHeight, &nrChannels, 0);
                }
                else
                {
                    // Direct file loading - much faster than loading to memory first
                    pixelData = stbi_load(fileName.c_str(), &imageWidth, &imageHeight, &nrChannels, 0);
                }
                
                if (pixelData)
                {
                    this->width = imageWidth;
                    this->height = imageHeight;
                    this->numberOfChannels = nrChannels;
                    
                    created = Create(pixelData, width, height, numberOfChannels);
                    
                    stbi_image_free(pixelData);
                    pixelData = nullptr;
                }
            }
            
            done = true;
        }
        catch(const std::exception& e)
        {
            std::cerr << "Texture loading failed: " << e.what() << std::endl;
            done = true; // Mark as done even on failure
        }
    }
}
