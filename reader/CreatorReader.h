/****************************************************************************
 Copyright (c) 2017 Chukong Technologies Inc.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/
#pragma once

#include <map>
#include <mutex>
#include <thread>
#include <memory>
#include <unordered_map>

#define CREATOR_ENABLE_SPINE 0

#if CREATOR_ENABLE_SPINE
#include <spine/spine-cocos2dx.h>
#endif

#include "cocos2d.h"
#include "ui/CocosGUI.h"

#include "core/SpriteFrameCache.h"

#include "animation/AnimationClip.h"
#include "animation/AnimationManager.h"

#include "Macros.h"
#include "helpers/Helper.h"

#include "CreatorReader_generated.h"
#include "Animation_generated.h"
#include "collider/ColliderManager.h"

//#include "dragonbones/DragonBonesHeaders.h"
//#include "dragonbones/cocos2dx/CCDragonBonesHeaders.h"

NS_CCR_BEGIN

// Forward declarations
class Layout;
class Button;
class ScrollView;
class ParticleSystem;
class WidgetManager;
class RichText;

class Reader
{
	friend class SpriteFrameCache;
private:
	static Reader* instance;

	// Based on the device quality, this can be changed to scale a sprite up/down if
	// you are using multiple quality of assets (HD/SD)
	float m_SpriteRectScale;

	// Same as above, this can be used to fetch non-atlas sprites from HD/SD directories
	std::string m_SpriteBasePath;

	// If you wish to replace any paths while reading spriteframes, use this!
	std::unordered_map<std::string, std::string> m_PathReplacements;
	
	bool m_ParsingScene = false;

	bool m_Ready = true;
	std::mutex m_Mutex;
	std::condition_variable m_RunIfFree;

public:
	static Reader* i() { return Reader::instance; }

	Reader();
	~Reader();

	bool loadScene(const std::string& filename);
	bool loadPrefab(const std::string& filename);
	void loadPrefabAsync(const std::string& filename, const std::function<void(cocos2d::Node*)>& callback);

	inline void SetSpriteRectScale(float value) { m_SpriteRectScale = value; }
	inline float GetSpriteRectScale() const { return m_SpriteRectScale; }
	inline void SetSpriteBasePath(const std::string& value) { m_SpriteBasePath = value; }
	inline std::string GetSpriteBasePath() const { return m_SpriteBasePath; }
	inline void AddPathReplacement(const std::string& src, const std::string& dst) { m_PathReplacements.emplace(src, dst); }

	/**
     Resets reader
     @return A `Scene*`
     */
	void Reset();

	/**
     Returns the scenegraph contained in the .ccreator file
     @return A `Scene*`
     */
	cocos2d::Scene* getSceneGraph();

	/**
     Returns the node graph contained in the .ccreator file
     @return A `Node*`
     */
	cocos2d::Node* getNodeGraph(cocos2d::Vec2* positionDiff = nullptr);

	/**
     Return the AnimationManager. It is added as a child of the Scene to simplify the codes.
     @return The `AnimationManager` of the scene
     */
	AnimationManager* getAnimationManager() const;

	/**
     Return the WidgetManager. It is added as a child of the Scene to make Creator Widget component take effect.
     @return The `WidgetManager` of the scene
     */
	WidgetManager* getWidgetManager() const;

	/**
     Return the CollisionManager. It is added as a child of the Scene to make collision take effect.
     @return The `CollisionManager` of the scene
     */
	ColliderManager* getColliderManager() const;

	/**
     Returns the FlatBuffers Schema version.
     @return a string containing the flatbuffer's schema version
     */
	std::string getVersion() const;

	// Adjusts positions of all the child nodes recursively
	void adjustPositionRecursively(cocos2d::Node* root) const;

protected:
	/**
	 Setup the needed spritesheets and change the design resolution if needed.
	 Call it before getting the Scene graph
	 */
	virtual void setupScene();
	virtual void setupPrefab(const void* buffer = nullptr);

	cocos2d::Node* createTree(const buffers::NodeTree* treeBuffer) const;

	cocos2d::Scene* createScene(const buffers::Scene* sceneBuffer) const;
	void parseScene(cocos2d::Scene* scene, const buffers::Scene* sceneBuffer) const;

	cocos2d::Node* createPrefabRoot(const buffers::Prefab* prefabBuffer) const;
	void parsePrefabRoot(cocos2d::Node* node, const buffers::Prefab* prefabBuffer) const;

	cocos2d::Node* createNode(const buffers::Node* nodeBuffer) const;
	void parseNode(cocos2d::Node* node, const buffers::Node* nodeBuffer) const;

	creator::Layout* createLayout(const buffers::Layout* nodeBuffer) const;
	void parseLayout(creator::Layout* node, const buffers::Layout* nodeBuffer) const;

	void parseNodeAnimation(cocos2d::Node* node, const buffers::Node* nodeBuffer) const;
	void parseColliders(cocos2d::Node* node, const buffers::Node* nodeBuffer) const;
	void parseWidget(cocos2d::Node* node, const buffers::Node* nodeBuffer) const;

	// For sliced sprites
	cocos2d::ui::Scale9Sprite* createScale9Sprite(const buffers::Sprite* spriteBuffer) const;
	void parseScale9Sprite(cocos2d::ui::Scale9Sprite* sprite, const buffers::Sprite* spriteBuffer) const;

	// For filled sprites
	cocos2d::ProgressTimer* createFilledSprite(const buffers::Sprite* spriteBuffer) const;
	void parseFilledSprite(cocos2d::ProgressTimer* sprite, const buffers::Sprite* spriteBuffer) const;

	cocos2d::Sprite* createSprite(const buffers::Sprite* spriteBuffer) const;
	void parseSprite(cocos2d::Sprite* sprite, const buffers::Sprite* spriteBuffer) const;
	void parseTrimmedSprite(cocos2d::Sprite* sprite) const;

	cocos2d::TMXTiledMap* createTileMap(const buffers::TileMap* tilemapBuffer) const;
	void parseTilemap(cocos2d::TMXTiledMap* tilemap, const buffers::TileMap* tilemapBuffer) const;

	cocos2d::Label* createLabel(const buffers::Label* labelBuffer) const;
	void parseLabel(cocos2d::Label* label, const buffers::Label* labelBuffer) const;

	creator::RichText* createRichText(const buffers::RichText* richTextBuffer) const;
	void parseRichText(creator::RichText* richText, const buffers::RichText* richTextBuffer) const;

	cocos2d::ParticleSystemQuad* createParticle(const buffers::Particle* particleBuffer) const;
	void parseParticle(creator::ParticleSystem* partile, const buffers::Particle* particleBuffer) const;

	cocos2d::ui::ScrollView* createScrollView(const buffers::ScrollView* scrollViewBuffer) const;
	void parseScrollView(cocos2d::ui::ScrollView* scrollView, const buffers::ScrollView* scrollViewBuffer) const;

	cocos2d::ui::LoadingBar* createProgressBar(const buffers::ProgressBar* progressBarBuffer) const;
	void parseProgressBar(cocos2d::ui::LoadingBar* progressBar, const buffers::ProgressBar* progressBarBuffer) const;

	cocos2d::ui::EditBox* createEditBox(const buffers::EditBox* editBoxBuffer) const;
	void parseEditBox(cocos2d::ui::EditBox* editBox, const buffers::EditBox* editBoxBuffer) const;

	cocos2d::ui::Button* createButton(const buffers::Button* buttonBuffer) const;
	void parseButton(creator::Button* button, const buffers::Button* buttonBuffer) const;

#if CREATOR_ENABLE_SPINE
	spine::SkeletonAnimation* createSpineSkeleton(const buffers::SpineSkeleton* spineBuffer) const;
	void parseSpineSkeleton(spine::SkeletonAnimation* button, const buffers::SpineSkeleton* spineBuffer) const;
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	cocos2d::experimental::ui::VideoPlayer* createVideoPlayer(const buffers::VideoPlayer* videoPlayerBuffer) const;
	void parseVideoPlayer(cocos2d::experimental::ui::VideoPlayer* videoPlayer, const buffers::VideoPlayer* videoPlayerBuffer) const;

	cocos2d::experimental::ui::WebView* createWebView(const buffers::WebView* webViewBuffer) const;
	void parseWebView(cocos2d::experimental::ui::WebView* webView, const buffers::WebView* webViewBuffer) const;
#endif

	cocos2d::ui::Slider* createSlider(const buffers::Slider* sliderBuffer) const;
	void parseSlider(cocos2d::ui::Slider* slider, const buffers::Slider* sliderBuffer) const;

	cocos2d::ui::CheckBox* createToggle(const buffers::Toggle* toggleBuffer) const;
	void parseToggle(cocos2d::ui::CheckBox* checkBox, const buffers::Toggle* toggleBuffer) const;

	cocos2d::ui::RadioButtonGroup* createToggleGroup(const buffers::ToggleGroup* toggleGroupBuffer) const;
	void parseToggleGroup(cocos2d::ui::RadioButtonGroup* radioGroup, const buffers::ToggleGroup* toggleGroupBuffer) const;

	cocos2d::ui::PageView* createPageView(const buffers::PageView* pageViewBuffer) const;
	void parsePageView(cocos2d::ui::PageView* pageview, const buffers::PageView* pageViewBuffer) const;

	cocos2d::ClippingNode* createMask(const buffers::Mask* maskBuffer) const;
	void parseMask(cocos2d::ClippingNode* mask, const buffers::Mask* maskBuffer) const;

	//dragonBones::CCArmatureDisplay* createArmatureDisplay(const buffers::DragonBones* dragonBonesBuffer) const;
	//void parseArmatureDisplay(dragonBones::CCArmatureDisplay* armatureDisplay, const buffers::DragonBones* dragonBonesBuffer) const;

	cocos2d::MotionStreak* createMotionStreak(const buffers::MotionStreak* motionStreakBuffer) const;
	void parseMotionStreak(cocos2d::MotionStreak* motionStreak, const buffers::MotionStreak* motionStreakBuffer) const;

	void setupSpriteFrames();
	void setupCollisionMatrix();

	/** Creator uses parent's anchorpoint for child positioning.
     cocos2d-x uses parent's (0,0) for child positioning
     this function adjust that */
	void adjustPosition(cocos2d::Node* node) const;

	// variables
	std::string _lastReadFile;
	cocos2d::Data _data;
	std::string _version;

	AnimationManager* _animationManager;
	ColliderManager* _collisionManager;
	WidgetManager* _widgetManager;
	SpriteFrameCache* m_SpriteFrameCache;

	// creator will make scene at the center of screen when apply design solution strategy, cocos2d-x doesn't do it like this
	// this value record the diff
	cocos2d::Vec2 _positionDiffDesignResolution;

	CREATOR_DISALLOW_COPY_ASSIGN_AND_MOVE(Reader);
};

NS_CCR_END
