#pragma once

#include <string>

namespace xit::OpenGL
{
    /// <summary>
    /// An Asset is something which is used in the scene, but is not in the scene 
    /// tree. An example of an asset is a material, which there may be one instance
    /// of which is shared between many objects.
    /// </summary>
    class Asset
    {
    private:
        int id;
        std::string name;

    public:
        Asset()
        {
            id = 0;
        }

        /// <summary>
        /// Gets or sets the id.
        /// </summary>
        /// <value>
        /// The id.
        /// </value>
        const int& Id = id;
        void SetId(int value)
        {
            if (id != value)
            {
                id = value;
            }
        }

            /// <summary>
            /// Gets or sets the name.
            /// </summary>
            /// <value>
            /// The name.
            /// </value>
        const std::string& Name = name;
        void SetName(const std::string& value)
        {
            if (name != value)
            {
                name = value;
            }
        }
    };
}
