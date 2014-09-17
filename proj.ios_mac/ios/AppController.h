#import <UIKit/UIKit.h>
#import "GADBannerView.h"
#import "GADInterstitial.h"

@class RootViewController;

@interface AppController : NSObject <UIApplicationDelegate, GADInterstitialDelegate> {
    UIWindow *window;
}

@property(nonatomic, readonly) RootViewController* viewController;

+(void) showBannerView;

+(void) hideBannerView;

+(void) showInterstitialView;

@end

