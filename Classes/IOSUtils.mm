//
//  IOSUtils.cpp
//  BoxGoHome
//
//  Created by 刘健 on 14-9-12.
//
//

#include "IOSUtils.h"
#include "AppController.h"

void IOSUtils::showBannerView()
{
    [AppController showBannerView];
}

void IOSUtils::hideBannerView()
{
    [AppController hideBannerView];
}

void IOSUtils::showInterstitialView()
{
    [AppController showInterstitialView];
}
