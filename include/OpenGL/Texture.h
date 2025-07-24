#pragma once

#include <map>

#include <IO/IO.h>
#include <Application/App.h>
#include <OpenGL/Asset.h>

#ifndef GLAD_INCLUDED
#include <glad/glad.h>
#define GLAD_INCLUDED
#endif

namespace xit::OpenGL
{
    /**
     * @brief A Texture object is simply an array of bytes. It has OpenGL functions, but is
     * not limited to OpenGL, so DirectX or custom library functions could be later added.
     */
    class Texture : public OpenGL::Asset
    {
    private:
        static std::map<std::string, Texture> textures;
        static std::list<std::string> failedImages;
        static int textureMaxSize;
        
        bool created = false;
        bool done = false;
        int numberOfChannels = 0;

        /**
         * @brief This is an array of bytes (r, g, b, a) that represent the pixels in this
         * texture object.
         */
        unsigned char* pixelData = nullptr;

        /**
         * @brief The width of the texture image.
         */
        int width = 0;

        /**
         * @brief The height of the texture image.
         */
        int height = 0;

        /**
         * @brief This is for OpenGL textures, it is the unique ID for the OpenGL texture.
         */
        GLuint textureId = 0;

        void CreateAsync();

    public:
        const int& Width = width;
        const int& Height = height;

        /**
         * @brief Gets the name of the texture.
         * @return The name of the texture.
         */
        GLuint TextureName();

        /**
         * @brief Gets the number of channels of the texture.
         * @return The number of channels of the texture.
         */
        GLuint GetChannels() const;

        bool GetIsCreated() const { return created; }
        bool GetIsDone() const { return done; }

        /**
         * @brief Initializes a new instance of the <see cref="Texture"/> class.
         */
        Texture() = default;

        /**
         * @brief Bind to the specified OpenGL instance.
         * @param gl The OpenGL instance.
         */
        void Bind() const;

        /**
         * @brief Unbind from the specified OpenGL instance.
         */
        void Unbind() const;

        /**
         * @brief This function creates the underlying OpenGL object.
         * @return True if the texture was successfully created.
         */
        virtual bool Create();

        /**
         * @brief This function creates the texture from an image.
         * @param data The image data.
         * @param width The width of the image.
         * @param height The height of the image.
         * @param nrChannels The number of channels in the image.
         * @return True if the texture was successfully loaded.
         */
        virtual bool Create(unsigned char* data, int width, int height, int nrChannels);

        /**
         * @brief This function creates the texture from an image file.
         * @param path The path to the image file.
         * @param width The width of the image.
         * @param height The height of the image.
         * @return True if the texture was successfully loaded.
         */
        virtual bool Create(const std::string& path, int width, int height);

        /**
         * @brief This function destroys the OpenGL object that is a representation of this texture.
         */
        virtual void Destroy();

        /**
         * @brief This function (attempts) to make a bitmap from the raw data. The fact that
         * the byte array is a managed type makes it slightly more complicated.
         * @return The texture object as a Bitmap.
         */
        //virtual Bitmap ToBitmap();

    public:
        /**
         * @brief Finds or creates a texture.
         * @param file The path to the image file.
         * @param width The width of the image.
         * @param height The height of the image.
         * @return The texture object.
         */
        static const Texture* FindOrCreateTexture(const std::string& file, int width, int height);
    };
}
