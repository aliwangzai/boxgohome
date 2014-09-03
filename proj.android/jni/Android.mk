LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/HelloWorldScene.cpp \
				   ../../Classes/ArrowSprite.cpp \
				   ../../Classes/BoxSprite.cpp \
				   ../../Classes/CheckBox.cpp \
				   ../../Classes/Dialog.cpp \
				   ../../Classes/DialogManager.cpp \
				   ../../Classes/LevelComplete.cpp \
				   ../../Classes/LevelCompleteLoss.cpp \
				   ../../Classes/Background.cpp \
				   ../../Classes/GameMap.cpp \
				   ../../Classes/GameUI.cpp \
				   ../../Classes/GameWorld.cpp \
				   ../../Classes/LevelSelector.cpp \
				   ../../Classes/MenuLayer.cpp \
				   ../../Classes/PlayGameMenu.cpp \
				   ../../Classes/Welcome.cpp \
				   ../../Classes/ContactLogic.cpp \
				   ../../Classes/Utils.cpp \
				   ../../Classes/VisibleRect.cpp \
				   ../../Classes/BlueWall.cpp \
				   ../../Classes/Wall.cpp \
				   ../../Classes/WoodenCrate.cpp \
				   ../../Classes/YellowWall.cpp \

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static

# LOCAL_WHOLE_STATIC_LIBRARIES += box2d_static
# LOCAL_WHOLE_STATIC_LIBRARIES += cocosbuilder_static
# LOCAL_WHOLE_STATIC_LIBRARIES += spine_static
# LOCAL_WHOLE_STATIC_LIBRARIES += cocostudio_static
# LOCAL_WHOLE_STATIC_LIBRARIES += cocos_network_static
# LOCAL_WHOLE_STATIC_LIBRARIES += cocos_extension_static


include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)
$(call import-module,audio/android)

# $(call import-module,Box2D)
# $(call import-module,editor-support/cocosbuilder)
# $(call import-module,editor-support/spine)
# $(call import-module,editor-support/cocostudio)
# $(call import-module,network)
# $(call import-module,extensions)
