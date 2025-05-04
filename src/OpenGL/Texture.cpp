#include <OpenGL/Texture.h>
#include <Threading/Dispatcher.h>
#include <Security/Cryptography.h>
#include <Application/App.h>
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
        //  Try and load the bitmap. Return false on failure.
        try
        {
            std::string fileName = path; // TODO File::Find(path);

            if (!fileName.empty())
            {
                int imageWidth, imageHeight, nrChannels;

                std::vector<char> bytes;

                if (fileName.ends_with(".enc"))
                {
                    bytes = Security::Cryptography::DecryptFromFile(fileName, App::GetPassword());
                }
                else
                {
                    bytes = File::ReadAllBytes(fileName);
                }

                pixelData = stbi_load_from_memory((unsigned char *)bytes.data(), bytes.size(), &imageWidth, &imageHeight, &nrChannels, 0);

                if (!pixelData)
                    return false;

                this->width = imageWidth;
                this->height = imageHeight;
                this->numberOfChannels = nrChannels;

                Dispatcher::Invoke(std::bind(&Texture::CreateAsync, this));

                return true;
            }
        }
        catch (...)
        {
            // Couldn't load the image; probably because of an invalid path
        }

        return false;
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

        // Create a new texture entry in the map.
        Texture &texture = textures[file];

        // Unlock the mutex before creating the texture.
        lock.unlock();

        // Create the texture.
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
}
