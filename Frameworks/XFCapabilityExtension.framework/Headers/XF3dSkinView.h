//
//  XF3dSkinView.h
//  XFCapabilityExtension
//
//  Created by 胡文峰 on 2019/11/15.
//  Copyright © 2019 XIAOFUTECH. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <GLKit/GLKit.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, XF3dSkinBGStyle) {
    XF3dSkinBGStyleNone = 0,  // 无背景
    XF3dSkinBGStyleRadialGradient,  // 径向渐变，k3dSkinBGColors examples like @[0x4c4e53, 0x121316]
    XF3dSkinBGStyleLinearGradient,  // 线性渐变
    
};  // 选择“3d影像预览”背景渲染类型


typedef NS_ENUM(NSInteger, XF3dSkinVersion) {
    XF3dSkinVersion20191120 = 0,  // 3d影像预览 v2.0
    XF3dSkinVersion20180801,  // 3d影像预览 v1.0
    
};  // 选择“3d影像预览”渲染版本


typedef NS_ENUM(NSInteger, XF3dSkinGestureMode) {
    XF3dSkinGestureModeFreedom = 0,  // 无限制，自由模式
    XF3dSkinGestureModeUser01,  // 有限制，用户模式01
    XF3dSkinGestureModeUser02,  // 有限制，用户模式02
    
};  // 选择手势操作模式


typedef NS_ENUM(NSInteger, XF3dSkinContentMode) {
    XF3dSkinContentModeScaleAspectFit = 0,
    XF3dSkinContentModeScaleAspectFill,
    XF3dSkinContentModeCenter,
    
};  // 选择“3d影像预览”渲染填充模式


struct _XF3dSkinStageStatus {
    long long status_id;  // 状态识别id
    GLKVector3 translate;
    GLKVector3 rotate;
    GLKVector3 scale;
    
};  // 设定“3d影像预览”舞台状态
typedef struct _XF3dSkinStageStatus XF3dSkinStageStatus;

struct _XF3dSkinStageDesign {
    BOOL preset;  // 是否显示静态图片
    
    BOOL InAnimate;  // 是否显示入场动画
    NSInteger inMode;  // 入场模式 < 0-从头开始，1-随机(状态数大于2时有效) >
    NSTimeInterval inAfterDelay;  // 入场动画延迟触发等待时长，
    NSTimeInterval inDuration;  // 入场动画持续时长
    NSTimeInterval inTimeinterval;  // 状态动画切换间隔
    NSArray *inSequence;  // 入场动画 状态序列
    
    BOOL loopAnimate;  // 是否显示循环动画
    NSInteger loopMode;  // 循环模式 < 0-从头开始，1-随机(状态数大于2时有效)，2-回溯循环 >
    NSTimeInterval loopAfterDelay;  // 循环动画延迟触发等待时长，在入场动画之后
    NSTimeInterval loopDuration;  // 循环动画持续时长
    NSTimeInterval loopTimeinterval;  // 状态动画切换间隔
    NSArray *loopSequence;  // 循环动画 状态序列
    
};  // 设定“3d影像预览”舞台 入场&展示 模式
typedef struct _XF3dSkinStageDesign XF3dSkinStageDesign;


// api 执行完成回调Block类型
typedef void (^XF3dSkinCallbackBlock)(NSInteger ret, NSError * _Nullable error);


#pragma mark ======== >> XF3dSkinView << ========
@interface XF3dSkinView : UIView
@property (nonatomic, strong) NSString *k3dSkinKey;  // api使用权限key
@property (nonatomic, strong) NSString *k3dSkinSecret;  // api使用权限secret

@property (nonatomic, assign, readonly) BOOL processing;  // default is NO (YES Means API Is Locked)

@property (nonatomic, assign) XF3dSkinBGStyle k3dSkinBGStyle;  // default is XF3dSkinBGStyleNone
@property (nonatomic, strong) NSArray<UIColor *> *k3dSkinBGColors;  // default is nil with XF3dSkinBGStyleNone

@property (nonatomic, assign) XF3dSkinVersion k3dSkinVersion;  // default is XF3dSkinVersion20191120
@property (nonatomic, assign) XF3dSkinContentMode kContentMode;  // default is XF3dSkinContentModeScaleAspectFit
@property (nonatomic, assign) XF3dSkinGestureMode kGestureMode;  // default is XF3dSkinGestureModeUser01

/*
 kStageStatusPreset >> Sdk 预设的一些舞台状态 - XF3dSkinStageStatus
 kStageDesignPreset >> Sdk 预设的一些舞台 入场&展示 模式 - XF3dSkinStageDesign
 kStageDesign >> default is kStageDesignPreset.firstObject
 kStageFrameRate >> 入场&展示 动画帧率：24 ~ 120，默认 24
 
 注意：上述属性（不包含`kStageFrameRate`）受属性`k3dSkinVersion`，`frame`和`kContentMode`设定的影响
 */
@property (nonatomic, strong, readonly) NSArray *kStageStatusPreset;
@property (nonatomic, strong, readonly) NSArray *kStageDesignPreset;
@property (nonatomic, assign) XF3dSkinStageDesign kStageDesign;
@property (nonatomic, assign) NSInteger kStageFrameRate;

/// 显示特定图片的 3d影像预览
/// @param filePath 图片本地路径
/// @param completion 预览处理完成回调
- (void)skin3dImageRenderingWithFilePath:(NSString *)filePath
                              Completion:(XF3dSkinCallbackBlock _Nullable)completion;


/// 获取当前 3d影像预览 的渲染快照
- (NSArray *)snapshot;

@end

NS_ASSUME_NONNULL_END
