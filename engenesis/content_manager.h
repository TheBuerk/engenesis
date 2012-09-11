#ifndef CONTENT_MANAGER_H_INCLUDED
#define CONTENT_MANAGER_H_INCLUDED

#include "main.h"
#include "config.h"
#include "non_copyable.h"
#include <map>
#include <string>
#include "exception.h"

namespace egn
{

    /**
    * @class ContentManager
    * @brief A very simple interface to get resources from files. Use the get() method to get the resource.
    *        The file will be opened only the first time. This class is non-copyable.
    */
    template <typename T>
    class EGNAPI ContentManager : public egn::NonCopyable
    {
        public:
            typedef std::map<std::string , T*> CMap;
            /**
            * @brief Default constuctor
            */
            ContentManager() { }

            /**
            * @brief Destructor
            */
            ~ContentManager()
            {
                typename CMap::iterator it;
                for(it = mResources.begin(); it != mResources.end(); ++it)
                {
                    delete it->second;
                }
            }


            /**
            * @brief Returns a Resource data from the given file
            * @param filepath The file path of the resource
            */
            T& get(const std::string& filepath)
            {
                if(mResources.find(filepath) == mResources.end()) // Non trouvée, on va charger la ressource pour la première fois
                {
                    ILOG << "Loading " << filepath << " ..." << std::endl;
                    T* content = new T();
                    if(!content->loadFromFile(filepath))
                    {
                        FLOG << "Resource " << filepath << "does not exists !" << std::endl;
                        throw(egn::exception("COuld not open resource " + filepath, __FILE__, __LINE__));
                    }

                    mResources[filepath] = content;
                    return *content;
                }


                return *mResources[filepath];
            }




        private:
            std::map<std::string , T*>    mResources;
    };


}

#endif // CONTENT_MANAGER_H_INCLUDED
