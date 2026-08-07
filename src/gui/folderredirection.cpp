#include "folderredirection.h"
#include "folder.h"

#ifdef Q_OS_WIN

#include "common/utility_win.h"

#include <array>
#include <windows.h> //PWSTR, FAILED, CoTaskMemFree
#include <shlobj.h> // SHGetKnownFolderPath

#endif


namespace OCC 
{
    Q_LOGGING_CATEGORY(lcFolderRedirection, "gui.folderredirection", QtInfoMsg)

    #ifdef Q_OS_WIN
    const QString policyKeyPath = QStringLiteral("HKEY_LOCAL_MACHINE\\SOFTWARE\\Policies\\ownCloud\\ownCloud\\FolderRedirection");

    //Declare GUIDs of known folders that can be redirected.
    struct KnownFolderMapping
    {
        const char *name;
        GUID id;
    };

    // Maybe define each GUID as a variable, but probably unnecessary. Will decide later.
    const std::array<KnownFolderMapping, 9> knownFolders = { {
        { "Desktop", { 0xB4BFCC3A, 0xDB2C, 0x424C, { 0xB0, 0x29, 0x7F, 0xE9, 0x9A, 0x87, 0xC6, 0x41 } } },
        { "Documents", { 0xFDD39AD0, 0x238F, 0x46AF, { 0xAD, 0xB4, 0x6C, 0x85, 0x48, 0x03, 0x69, 0xC7 } } },
        { "Pictures", { 0x33E28130, 0x4E1E, 0x4676, { 0x83, 0x5A, 0x98, 0x39, 0x5C, 0x3B, 0xC3, 0xBB } } },
        { "Downloads", { 0x374DE290, 0x123F, 0x4565, { 0x91, 0x64, 0x39, 0xC4, 0x92, 0x5E, 0x46, 0x7B } } },
        { "Music", { 0x4BD8D571, 0x6D19, 0x48D3, { 0xBE, 0x97, 0x42, 0x22, 0x20, 0x08, 0x0E, 0x43 } } },
        { "Videos", { 0x18989B1D, 0x99B5, 0x455B, { 0x84, 0x1C, 0xAB, 0x7C, 0x74, 0xE4, 0xDD, 0xFC } } },
        { "Favorites", { 0x1777F761, 0x68AD, 0x4D8A, { 0x87, 0xBD, 0x30, 0xB7, 0x59, 0xFA, 0x33, 0xDD } } },
        { "Contacts", { 0x56784854, 0xC6CB, 0x462B, { 0x81, 0x69, 0x88, 0xE3, 0x50, 0xAC, 0xB8, 0x82 } } },
        { "Links", { 0xBFB9D5E0, 0xC6A9, 0x404C, { 0xB2, 0xB2, 0xAE, 0x6D, 0xB6, 0xAF, 0x49, 0x68 } } },
    } };

    // Get folder path for the specified folder ID.
    // Returns empty on failure.
    QString getCurrentFolderPath(const GUID &id)
    {
        PWSTR raw = nullptr;
        const HRESULT hr = SHGetKnownFolderPath(id, 0, nullptr, &raw);
        if (FAILED(hr) || !raw) {
            if (raw) {
                CoTaskMemFree(raw);
            }
            return {};
        }
        const QString path = QString::fromWCharArray(raw);
        CoTaskMemFree(raw);
        return path;
    }


    void FolderRedirection::applyOnSyncFinished(Folder *triggeringFolder, bool syncSuccessful)
    {
        //Placeholder, no code yet.
        
        //Test code to see if folder paths are gettable. 
        for (const auto &folder : knownFolders)
        {
            const QString path = getCurrentFolderPath(folder.id);
            qCInfo(lcFolderRedirection) << folder.name << path;
        }
    }

    #endif
}