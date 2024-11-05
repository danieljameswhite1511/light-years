#pragma once
#include <functional>

#include "Core.h"
#include "Object.h"

namespace ly {
    template<typename ... Args>
    class Delegate {
        public:

        template<typename ClassName>
        //this is the syntax for pointer to member function void (ClassName::*callback)(Args...)
        void BindToAction(weak<Object> obj, void (ClassName::*callback)(Args...)) {

            std::function<bool(Args...)> callbackFunction = [obj, callback](Args... args)->bool {

                if (!obj.expired()) {
                    (static_cast<ClassName*>(obj.lock().get())->*callback)(args...);
                    return true;
                }
                return false;
            };

            mCallbacks.push_back(callbackFunction);
        };

        void Broadcast(Args... args) {
            for (auto iter = mCallbacks.begin(); iter != mCallbacks.end();) {
                if((*iter)(args...)) {
                    ++iter;
                }else {
                    mCallbacks.erase(iter);
                }
            }
        }

        private:
        List<std::function<bool(Args...)>> mCallbacks;

    };
}
