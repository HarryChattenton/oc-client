// Known Folder Redirection

namespace OCC 
{
    class Folder;

    namespace FolderRedirection 
    {
        void applyOnSyncFinished(Folder *triggeringFolder, bool syncSuccessful); // Run the redirection after the personal space finishes syncing.
    }
}