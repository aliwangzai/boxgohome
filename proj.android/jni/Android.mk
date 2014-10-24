LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/extensions)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/HelloWorldScene.cpp \
				   ../../Classes/ArrowSprite.cpp \
				   ../../Classes/BoxSprite.cpp \
				   ../../Classes/CheckBox.cpp \
				   ../../Classes/Dialog.cpp \
				   ../../Classes/UIButton.cpp \
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
				   ../../Classes/BaseEntity.cpp \
				   ../../Classes/WoodenCrate.cpp \
				   ../../Classes/YellowWall.cpp \
				   ../../Classes/Enemy.cpp \
				   ../../Classes/JumpsItem.cpp \
				   ../../Classes/TailEffect.cpp \
				   ../../Classes/BrokableWall.cpp \
				   ../../Classes/ShareManager.cpp \
				   ../../Classes/AdManager.cpp \
				   ../../Classes/SettingsDiaog.cpp \
				   ../../Classes/TutorialMenu.cpp \
				   ../../Classes/C2DXShareSDK/Android/JSON/cJSON/cJSON.c \
				   ../../Classes/C2DXShareSDK/Android/JSON/CCJSONConverter.cpp \
				   ../../Classes/C2DXShareSDK/Android/ShareSDKUtils.cpp \
				   ../../Classes/C2DXShareSDK/C2DXShareSDK.cpp \
				   
LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../Classes/C2DXShareSDK
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../Classes/C2DXShareSDK/Android
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../Classes/C2DXShareSDK/Android/JSON
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../Classes/C2DXShareSDK/Android/JSON/cJSON

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_extension_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_ui_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocostudio_static

# LOCAL_WHOLE_STATIC_LIBRARIES += box2d_static
# LOCAL_WHOLE_STATIC_LIBRARIES += cocosbuilder_static
# LOCAL_WHOLE_STATIC_LIBRARIES += spine_static
# LOCAL_WHOLE_STATIC_LIBRARIES += cocostudio_static
# LOCAL_WHOLE_STATIC_LIBRARIES += cocos_network_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)
$(call import-module,audio/android)
$(call import-module,ui)
$(call import-module,extensions)
$(call import-module,editor-support/cocostudio)

# $(call import-module,Box2D)
# $(call import-module,editor-support/cocosbuilder)
# $(call import-module,editor-support/spine)
# $(call import-module,editor-support/cocostudio)
# $(call import-module,network)
# $(call import-module,extensions)
