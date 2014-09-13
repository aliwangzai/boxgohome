#import <UIKit/UIKit.h>
#import "GADBannerView.h"

@class RootViewController;

@interface AppController : NSObject <UIApplicationDelegate> {
    UIWindow *window;
}

@property(nonatomic, readonly) RootViewController* viewController;

+(void) showBannerView;

+(void) hideBannerView;

@end

