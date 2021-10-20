(function(g){var window=this;'use strict';var B6=function(a){g.V.call(this,{G:"div",L:"ytp-miniplayer-ui"});this.qe=!1;this.player=a;this.T(a,"minimized",this.wg);this.T(a,"onStateChange",this.xG)},C6=function(a){g.ZM.call(this,a);
this.i=new B6(this.player);this.i.hide();g.MM(this.player,this.i.element,4);a.Le()&&(this.load(),g.N(a.getRootNode(),"ytp-player-minimized",!0))};
g.v(B6,g.V);g.k=B6.prototype;
g.k.sE=function(){this.tooltip=new g.yQ(this.player,this);g.I(this,this.tooltip);g.MM(this.player,this.tooltip.element,4);this.tooltip.scale=.6;this.uc=new g.SN(this.player);g.I(this,this.uc);this.Bg=new g.V({G:"div",L:"ytp-miniplayer-scrim"});g.I(this,this.Bg);this.Bg.Ea(this.element);this.T(this.Bg.element,"click",this.jA);var a=new g.V({G:"button",Ga:["ytp-miniplayer-close-button","ytp-button"],W:{"aria-label":"Close"},U:[g.TK()]});g.I(this,a);a.Ea(this.Bg.element);this.T(a.element,"click",this.Bi);
a=new g.V1(this.player,this);g.I(this,a);a.Ea(this.Bg.element);this.vp=new g.V({G:"div",L:"ytp-miniplayer-controls"});g.I(this,this.vp);this.vp.Ea(this.Bg.element);this.T(this.vp.element,"click",this.jA);var b=new g.V({G:"div",L:"ytp-miniplayer-button-container"});g.I(this,b);b.Ea(this.vp.element);a=new g.V({G:"div",L:"ytp-miniplayer-play-button-container"});g.I(this,a);a.Ea(this.vp.element);var c=new g.V({G:"div",L:"ytp-miniplayer-button-container"});g.I(this,c);c.Ea(this.vp.element);this.iN=new g.pP(this.player,
this,!1);g.I(this,this.iN);this.iN.Ea(b.element);b=new g.nP(this.player,this);g.I(this,b);b.Ea(a.element);this.nextButton=new g.pP(this.player,this,!0);g.I(this,this.nextButton);this.nextButton.Ea(c.element);this.Eg=new g.jQ(this.player,this);g.I(this,this.Eg);this.Eg.Ea(this.Bg.element);this.Fc=new g.wP(this.player,this);g.I(this,this.Fc);g.MM(this.player,this.Fc.element,4);this.Xz=new g.V({G:"div",L:"ytp-miniplayer-buttons"});g.I(this,this.Xz);g.MM(this.player,this.Xz.element,4);a=new g.V({G:"button",
Ga:["ytp-miniplayer-close-button","ytp-button"],W:{"aria-label":"Close"},U:[g.TK()]});g.I(this,a);a.Ea(this.Xz.element);this.T(a.element,"click",this.Bi);a=new g.V({G:"button",Ga:["ytp-miniplayer-replay-button","ytp-button"],W:{"aria-label":"Close"},U:[g.YK()]});g.I(this,a);a.Ea(this.Xz.element);this.T(a.element,"click",this.xV);this.T(this.player,"presentingplayerstatechange",this.Mc);this.T(this.player,"appresize",this.wb);this.T(this.player,"fullscreentoggled",this.wb);this.wb()};
g.k.show=function(){this.Jd=new g.Dq(this.iq,null,this);this.Jd.start();this.qe||(this.sE(),this.qe=!0);0!==this.player.getPlayerState()&&g.V.prototype.show.call(this);this.Fc.show();this.player.unloadModule("annotations_module")};
g.k.hide=function(){this.Jd&&(this.Jd.dispose(),this.Jd=void 0);g.V.prototype.hide.call(this);this.player.Le()||(this.qe&&this.Fc.hide(),this.player.loadModule("annotations_module"))};
g.k.ya=function(){this.Jd&&(this.Jd.dispose(),this.Jd=void 0);g.V.prototype.ya.call(this)};
g.k.Bi=function(){this.player.stopVideo();this.player.Na("onCloseMiniplayer")};
g.k.xV=function(){this.player.playVideo()};
g.k.jA=function(a){if(a.target===this.Bg.element||a.target===this.vp.element)this.player.V().N("kevlar_miniplayer_play_pause_on_scrim")?g.WJ(this.player.xb())?this.player.pauseVideo():this.player.playVideo():this.player.Na("onExpandMiniplayer")};
g.k.wg=function(){g.N(this.player.getRootNode(),"ytp-player-minimized",this.player.Le())};
g.k.md=function(){this.Fc.Wb();this.Eg.Wb()};
g.k.iq=function(){this.md();this.Jd&&this.Jd.start()};
g.k.Mc=function(a){g.U(a.state,32)&&this.tooltip.hide()};
g.k.wb=function(){g.JP(this.Fc,0,this.player.bb().getPlayerSize().width,!1);g.xP(this.Fc)};
g.k.xG=function(a){this.player.Le()&&(0===a?this.hide():this.show())};
g.k.dc=function(){return this.tooltip};
g.k.Te=function(){return!1};
g.k.tf=function(){return!1};
g.k.ri=function(){return!1};
g.k.WA=function(){};
g.k.Ym=function(){};
g.k.Tr=function(){};
g.k.An=function(){return null};
g.k.jj=function(){return new g.El(0,0,0,0)};
g.k.handleGlobalKeyDown=function(){return!1};
g.k.handleGlobalKeyUp=function(){return!1};
g.k.qq=function(a,b,c,d,e){var f=0,h=d=0,l=g.Wl(a);if(b){c=g.Oq(b,"ytp-prev-button")||g.Oq(b,"ytp-next-button");var m=g.Oq(b,"ytp-play-button"),n=g.Oq(b,"ytp-miniplayer-expand-watch-page-button");c?f=h=12:m?(b=g.Ul(b,this.element),h=b.x,f=b.y-12):n&&(h=g.Oq(b,"ytp-miniplayer-button-top-left"),f=g.Ul(b,this.element),b=g.Wl(b),h?(h=8,f=f.y+40):(h=f.x-l.width+b.width,f=f.y-20))}else h=c-l.width/2,d=25+(e||0);b=this.player.bb().getPlayerSize().width;e=f+(e||0);l=g.Xf(h,0,b-l.width);e?(a.style.top=e+"px",
a.style.bottom=""):(a.style.top="",a.style.bottom=d+"px");a.style.left=l+"px"};
g.k.showControls=function(){};
g.k.Yk=function(){};
g.k.zk=function(){return!1};g.v(C6,g.ZM);C6.prototype.create=function(){};
C6.prototype.Ji=function(){return!1};
C6.prototype.load=function(){this.player.hideControls();this.i.show()};
C6.prototype.unload=function(){this.player.showControls();this.i.hide()};g.YM("miniplayer",C6);})(_yt_player);
