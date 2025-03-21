 // Workshop 8 - Smart Pointers
// 2019/11 - Cornel

#include <memory>
#include <utility>

#include <algorithm>

#include "DataBase.h"
#include "Profile.h"
#include "Utilities.h"

using namespace std;

namespace sdds {
    //DataBase<Profile> excludeRaw(const DataBase<Profile>& allProfiles, const DataBase<Profile>& bannedProfiles) {
    //    DataBase<Profile> result;

    //    try {
    //        // Loop through all profiles
    //        for (size_t i = 0; i < allProfiles.size(); i++) {
    //            bool found = false;

    //            // Loop through all banned profiles
    //            for (size_t j = 0; j < bannedProfiles.size(); j++) {
    //                // Check if a profile is equal to a banned profile
    //                // if it is, then it is excluded
    //                if (((allProfiles[i].m_name.first_name == bannedProfiles[j].m_name.first_name) &&
    //                    (allProfiles[i].m_name.last_name == bannedProfiles[j].m_name.last_name)) &&
    //                    allProfiles[i].m_age == bannedProfiles[j].m_age) {
    //                    found = true;
    //                    break; // No need to check further once found
    //                }
    //            }

    //            // If the profile is not found in banned profiles, then create it
    //            if (!found) {
    //                // Copy the Profile directly into the result
    //                result += &allProfiles[i];
    //            }
    //        }
    //    }
    //    catch (...) {
    //        // No need to delete objects, let the vector handle it
    //        throw; // Rethrow the exception
    //    }

    //    return result;
    //}
    //DataBase<Profile> excludeRaw(const DataBase<Profile>& allProfiles, const DataBase<Profile>& bannedProfiles) {
    //    DataBase<Profile> result;

    //    try {
    //        // Loop through all profiles
    //        for (size_t i = 0; i < allProfiles.size(); i++) {
    //            bool found = false;

    //            // Loop through all banned profiles
    //            for (size_t j = 0; j < bannedProfiles.size(); j++) {
    //                // Check if a profile is equal to a banned profile
    //                // if it is, then it is excluded
    //                if (((allProfiles[i].m_name.first_name == bannedProfiles[j].m_name.first_name) &&
    //                    (allProfiles[i].m_name.last_name == bannedProfiles[j].m_name.last_name)) &&
    //                    allProfiles[i].m_age == bannedProfiles[j].m_age) {
    //                    found = true;
    //                    break; // No need to check further once found
    //                }
    //            }

    //            // If the profile is not found in banned profiles, then add it to the result
    //            if (!found) {
    //                result += &allProfiles[i];
    //            }
    //        }
    //    }
    //    catch (...) {
    //        // No need to delete objects, let the vector handle it
    //        throw; // Rethrow the exception
    //    }

    //    return result;
    //}
    //DataBase<Profile> excludeRaw(const DataBase<Profile>& allProfiles, const DataBase<Profile>& bannedProfiles) {
    //    DataBase<Profile> result;

    //    // Loop all first parameter objects (allProfiles)
    //    for (auto i = 0u; i < allProfiles.size(); ++i) {
    //        bool isBanned = false;

    //        // Loop all second parameter objects
    //        for (auto j = 0u; j < bannedProfiles.size() && !isBanned; ++j) {

    //            // Find the matches object
    //            if (allProfiles[i].m_age == bannedProfiles[j].m_age &&
    //                allProfiles[i].m_name.first_name == bannedProfiles[j].m_name.first_name &&
    //                allProfiles[i].m_name.last_name == bannedProfiles[j].m_name.last_name) {
    //                isBanned = true;
    //            }
    //        }

    //        // If matches object not found
    //        if (!isBanned) {

    //            // Dynamic allocating current object
    //            Profile* newProfile = new Profile(allProfiles[i].m_name, allProfiles[i].m_address, allProfiles[i].m_age);

    //            try {
    //                // Validate address
    //                newProfile->validateAddress();

    //                // Add dynamic object to result
    //                result += newProfile;
    //            }
    //            catch (...) {
    //                // Deallocate dynamic object
    //                delete newProfile;

    //                throw;
    //            }

    //            // Deallocate dynamic object
    //            delete newProfile;
    //        }
    //    }
    //    // Return result
    //    return result;
    //}



DataBase<Profile> excludeRaw(const DataBase<Profile>& allProfiles, const DataBase<Profile>& bannedProfiles) {
    DataBase<Profile> result;
    Profile* newProfile = nullptr;

    // DONE: Add your code here to build a collection of Profiles.
    //         The result should contain only profiles from `allProfiles`
    //         which are not in `bannedProfiles` using Raw Pointers.
    bool found = false; // a flag if a profile is seen in a bad profile


    // Loop through all profiles
    for (size_t i = 0; i < allProfiles.size(); i++) {
        found = false;
        // Loop through all banned profiles
        for (auto j = 0u; j < bannedProfiles.size() && !found; ++j) {
            // Check if a profile is equal to a banned profile
            // if it is then it is excluded
            if (allProfiles[i].m_age == bannedProfiles[j].m_age &&
                allProfiles[i].m_name.first_name == bannedProfiles[j].m_name.first_name &&
                allProfiles[i].m_name.last_name == bannedProfiles[j].m_name.last_name) {
               found = true;
            }
        }
        // If profile is not found in banned profile
        // then create it
        if (!found) {
            newProfile = new Profile(allProfiles[i].m_name, allProfiles[i].m_address, allProfiles[i].m_age);
            // Validate the profile address
            // If profile addrress is valid, add it to the
            try {
                newProfile->validateAddress();
                result += newProfile;
               
            }
            catch (...) {
                delete newProfile;
                throw ;
            }
            delete newProfile;
        }

        // Check if there is an exception and deallocate memory if there is

    }
    return result;
}

DataBase<Profile> excludeSmart(const DataBase<Profile>& allProfiles, const DataBase<Profile>& bannedProfiles) {
    DataBase<Profile> result;

    // DONE: Add your code here to build a collection of Profiles.
    //         The result should contain only profiles from `allProfiles`
    //         which are not in `bannedProfiles` using Raw Pointers.
    bool found = false; // a flag if a profile is seen in a bad profile


    // Loop through all profiles
    for (size_t i = 0; i < allProfiles.size(); i++) {
        found = false;
        // Loop through all banned profiles
        for (auto j = 0u; j < bannedProfiles.size() && !found; ++j) {
            // Check if a profile is equal to a banned profile
            // if it is then it is excluded
            if (((allProfiles[i].m_name.first_name == bannedProfiles[j].m_name.first_name) && (allProfiles[i].m_name.last_name == bannedProfiles[j].m_name.last_name))
                && allProfiles[i].m_age == bannedProfiles[j].m_age) {
                found = true;
            }
        }
        // If profile is not found in banned profile
        // then create it
        if (!found) {
            //newProfile = new Profile(allProfiles[i].m_name, allProfiles[i].m_address, allProfiles[i].m_age);
            std::shared_ptr<Profile> newProfile(new Profile(allProfiles[i].m_name, allProfiles[i].m_address, allProfiles[i].m_age));
            // Validate the profile address
            // If profile addrress is valid, add it to the

            newProfile->validateAddress();
            result += newProfile;

        }
    }
    return result;
}




}