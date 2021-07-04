/**
 * The library is under a dual license, you can use either the Unlicense or the MIT license.
 */
#ifndef LIBLOADER_HPP
#define LIBLOADER_HPP

#include <LibLoader/LibHandle.hpp>
#include <vector>

namespace LibLoader
{
    /**
     * @brief Loads a library.
     * 
     * @param Path: Path to the library, without an extension or prefix such as "libNAME.so". 
     * @note If the library is already loaded, the loaded instance is returned.
     * 
     * @throw Throws a CLibException if any error occured while loading.
     */
    LibHandle LoadLibrary(const std::string &Path);

    /**
     * @brief Removes the handle from the cache.
     */
    void UnloadLibrary(LibHandle Library);

    /**
     * @return Returns a list of the loaded libraries.
     */
    std::vector<LibHandle> GetLoadedLibraries();
} // namespace LibLoader

#endif //LIBLOADER_HPP