/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2014 Chukong Technologies Inc.
 
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
package org.cocos2dx.cpp;

import org.cocos2dx.lib.Cocos2dxActivity;

import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.view.View;
import android.widget.RelativeLayout;
import android.widget.RelativeLayout.LayoutParams;
import cn.sharesdk.ShareSDKUtils;

import com.google.android.gms.ads.AdRequest;
import com.google.android.gms.ads.AdSize;
import com.google.android.gms.ads.AdView;

public class AppActivity extends Cocos2dxActivity {
	
	protected static final int GUIUPDATEIDENTIFIER = 0x101;
	
	private static AdView adBannerView;
	private static int adViewVisibility = View.GONE; 
	
	private static Handler adViewHandler = new Handler(){
		public void handleMessage(android.os.Message msg) {
			switch(msg.what){
			case GUIUPDATEIDENTIFIER:
				adBannerView.setVisibility(adViewVisibility);
				break;
			}
			super.handleMessage(msg);
		};
	};
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		
		adBannerView = new AdView(this);
		adBannerView.setAdUnitId("ca-app-pub-2906542859743654/2173098523");
		adBannerView.setAdSize(AdSize.BANNER);
	    AdRequest adRequest = new AdRequest.Builder().addTestDevice("37AD57E769A2AEB5D85343BAD6B050A8").build();
	    adBannerView.loadAd(adRequest);
	    
	    RelativeLayout relativeLayout = new RelativeLayout(this);
	    mFrameLayout.addView(relativeLayout);
	    LayoutParams layoutParams = new LayoutParams(
	    		LayoutParams.WRAP_CONTENT,LayoutParams.WRAP_CONTENT);
	    layoutParams.addRule(RelativeLayout.ALIGN_PARENT_TOP);
	    layoutParams.addRule(RelativeLayout.CENTER_HORIZONTAL, RelativeLayout.TRUE);
	    relativeLayout.addView(adBannerView, layoutParams);
	    
		ShareSDKUtils.prepare();
	}
	
	public static void showBannerAD(){
		System.out.println("showBannerAD---------------------------------------");
		adViewVisibility = View.VISIBLE;
		Message msg = new Message();
		msg.what = GUIUPDATEIDENTIFIER;
		adViewHandler.sendMessage(msg);
	}
	
	public static void hideBannerAD(){
		System.out.println("hideBannerAD---------------------------------------");
		adViewVisibility = View.GONE;
		Message msg = new Message();
		msg.what = GUIUPDATEIDENTIFIER;
		adViewHandler.sendMessage(msg);
	}
	
	@Override
	protected void onPause() {
		if( adBannerView != null) adBannerView.pause();
		super.onPause();
	}
	
	@Override
	protected void onResume() {
		if(adBannerView != null) adBannerView.resume();
		super.onResume();
	}
	
	@Override
	protected void onDestroy() {
		if(adBannerView != null) adBannerView.destroy();
		super.onDestroy();
	}
}
