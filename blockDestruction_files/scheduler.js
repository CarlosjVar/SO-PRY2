(function(){/*

 Copyright The Closure Library Authors.
 SPDX-License-Identifier: Apache-2.0
*/
'use strict';var g,aa="function"==typeof Object.create?Object.create:function(a){function b(){}
b.prototype=a;return new b},l;
if("function"==typeof Object.setPrototypeOf)l=Object.setPrototypeOf;else{var m;a:{var ba={a:!0},n={};try{n.__proto__=ba;m=n.a;break a}catch(a){}m=!1}l=m?function(a,b){a.__proto__=b;if(a.__proto__!==b)throw new TypeError(a+" is not extensible");return a}:null}var p=l;
function q(a,b){a.prototype=aa(b.prototype);a.prototype.constructor=a;if(p)p(a,b);else for(var c in b)if("prototype"!=c)if(Object.defineProperties){var d=Object.getOwnPropertyDescriptor(b,c);d&&Object.defineProperty(a,c,d)}else a[c]=b[c];a.X=b.prototype}
var t=this||self;function u(a){a=a.split(".");for(var b=t,c=0;c<a.length;c++)if(b=b[a[c]],null==b)return null;return b}
function ca(a,b,c){return a.call.apply(a.bind,arguments)}
function da(a,b,c){if(!a)throw Error();if(2<arguments.length){var d=Array.prototype.slice.call(arguments,2);return function(){var e=Array.prototype.slice.call(arguments);Array.prototype.unshift.apply(e,d);return a.apply(b,e)}}return function(){return a.apply(b,arguments)}}
function v(a,b,c){Function.prototype.bind&&-1!=Function.prototype.bind.toString().indexOf("native code")?v=ca:v=da;return v.apply(null,arguments)}
function w(a,b){a=a.split(".");var c=t;a[0]in c||"undefined"==typeof c.execScript||c.execScript("var "+a[0]);for(var d;a.length&&(d=a.shift());)a.length||void 0===b?c[d]&&c[d]!==Object.prototype[d]?c=c[d]:c=c[d]={}:c[d]=b}
;var y={},z=null;var ea="function"===typeof Uint8Array;function A(a){return null!==a&&"object"===typeof a&&a.constructor===Object}
function B(a,b){if(null!=a)return Array.isArray(a)||A(a)?C(a,b):b(a)}
function C(a,b){if(Array.isArray(a)){for(var c=Array(a.length),d=0;d<a.length;d++)c[d]=B(a[d],b);Array.isArray(a)&&a.R&&D(c);return c}c={};for(d in a)c[d]=B(a[d],b);return c}
function fa(a){switch(typeof a){case "number":return isFinite(a)?a:String(a);case "object":if(ea&&null!=a&&a instanceof Uint8Array){var b;void 0===b&&(b=0);if(!z){z={};for(var c="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789".split(""),d=["+/=","+/","-_=","-_.","-_"],e=0;5>e;e++){var f=c.concat(d[e].split(""));y[e]=f;for(var h=0;h<f.length;h++){var k=f[h];void 0===z[k]&&(z[k]=h)}}}b=y[b];c=Array(Math.floor(a.length/3));d=b[64]||"";for(e=f=0;f<a.length-2;f+=3){var r=a[f],x=a[f+1];
k=a[f+2];h=b[r>>2];r=b[(r&3)<<4|x>>4];x=b[(x&15)<<2|k>>6];k=b[k&63];c[e++]=""+h+r+x+k}h=0;k=d;switch(a.length-f){case 2:h=a[f+1],k=b[(h&15)<<2]||d;case 1:a=a[f],c[e]=""+b[a>>2]+b[(a&3)<<4|h>>4]+k+d}a=c.join("")}return a;default:return a}}
var ha={R:{value:!0,configurable:!0}};function D(a){Array.isArray(a)&&!Object.isFrozen(a)&&Object.defineProperties(a,ha);return a}
;var E;function F(a,b,c){var d=E;E=null;a||(a=d);d=this.constructor.W;a||(a=d?[d]:[]);this.h=(d?0:-1)-(this.constructor.V||0);this.g=a;a:{d=this.g.length;a=d-1;if(d&&(d=this.g[a],A(d))){this.j=a-this.h;this.i=d;break a}void 0!==b&&-1<b?(this.j=Math.max(b,a+1-this.h),this.i=null):this.j=Number.MAX_VALUE}if(c)for(b=0;b<c.length;b++)a=c[b],a<this.j?(a+=this.h,(d=this.g[a])?D(d):this.g[a]=G):(d=this.j+this.h,this.g[d]||(this.i=this.g[d]={}),(d=this.i[a])?D(d):this.i[a]=G)}
var G=Object.freeze(D([]));F.prototype.toJSON=function(){return C(this.g,fa)};
F.prototype.toString=function(){return this.g.toString()};function H(){this.s=this.s;this.B=this.B}
H.prototype.s=!1;H.prototype.dispose=function(){this.s||(this.s=!0,this.G())};
H.prototype.G=function(){if(this.B)for(;this.B.length;)this.B.shift()()};function I(a){F.call(this,a)}
q(I,F);var J,K,L,M=t.window,N=(null===(J=null===M||void 0===M?void 0:M.yt)||void 0===J?void 0:J.config_)||(null===(K=null===M||void 0===M?void 0:M.ytcfg)||void 0===K?void 0:K.data_)||{},O=(null===(L=null===M||void 0===M?void 0:M.ytcfg)||void 0===L?void 0:L.obfuscatedData_)||[];new I(O);w("yt.config_",N);w("yt.configJspb_",O);function P(a,b){return a in N?N[a]:b}
;function Q(a,b){a=ia(a);return void 0===a&&void 0!==b?b:Number(a||0)}
function ia(a){var b=P("EXPERIMENTS_FORCED_FLAGS",{});return void 0!==b[a]?b[a]:P("EXPERIMENT_FLAGS",{})[a]}
;var ja=Q("web_emulated_idle_callback_delay",300),ka=1E3/60-3;
function R(a){a=void 0===a?{}:a;H.call(this);this.g=[];this.g[8]=[];this.g[4]=[];this.g[3]=[];this.g[2]=[];this.g[1]=[];this.g[0]=[];this.j=0;this.N=a.timeout||1;this.i={};this.o=ka;this.C=this.h=this.m=0;this.D=this.l=!1;this.u=[];this.H=v(this.S,this);this.M=v(this.U,this);this.J=v(this.O,this);this.K=v(this.P,this);this.L=v(this.T,this);this.A=this.F=!1;var b;if(b=!!window.requestIdleCallback)b=ia("disable_scheduler_requestIdleCallback"),b=!("string"===typeof b&&"false"===b?0:b);this.I=b;(this.v=
!!a.useRaf&&!!window.requestAnimationFrame)&&document.addEventListener("visibilitychange",this.H)}
q(R,H);function la(a,b){var c=Date.now();S(b);b=Date.now()-c;a.l||(a.o-=b)}
function ma(a,b,c,d){++a.C;if(10==c)return la(a,b),a.C;var e=a.C;a.i[e]=b;a.l&&!d?a.u.push({id:e,priority:c}):(a.g[c].push(e),a.D||a.l||(0!=a.h&&T(a)!=a.m&&U(a),a.start()));return e}
function na(a){a.u.length=0;for(var b=4;0<=b;b--)a.g[b].length=0;a.g[8].length=0;a.i={};U(a)}
function T(a){if(a.g[8].length){if(a.A)return 4;if(!document.hidden&&a.v)return 3}for(var b=4;b>=a.j;b--)if(0<a.g[b].length)return 0<b?!document.hidden&&a.v?3:2:1;return 0}
function S(a){try{a()}catch(b){(a=u("yt.logging.errors.log"))&&a(b)}}
function oa(a){if(a.g[8].length)return!0;for(var b=3;0<=b;b--)if(a.g[b].length)return!0;return!1}
g=R.prototype;g.P=function(a){var b=void 0;a&&(b=a.timeRemaining());this.F=!0;V(this,b);this.F=!1};
g.U=function(){V(this)};
g.O=function(){pa(this)};
g.T=function(){this.A=!0;var a=T(this);4==a&&a!=this.m&&(U(this),this.start());V(this);this.A=!1};
g.S=function(){document.hidden||pa(this);this.h&&(U(this),this.start())};
function pa(a){U(a);a.l=!0;for(var b=Date.now(),c=a.g[8];c.length;){var d=c.shift(),e=a.i[d];delete a.i[d];e&&S(e)}qa(a);a.l=!1;oa(a)&&a.start();a.o-=Date.now()-b}
function qa(a){for(var b=0,c=a.u.length;b<c;b++){var d=a.u[b];a.g[d.priority].push(d.id)}a.u.length=0}
function V(a,b){a.A&&4==a.m&&a.h||U(a);a.l=!0;b=Date.now()+(b||a.o);for(var c=a.g[4];c.length;){var d=c.shift(),e=a.i[d];delete a.i[d];e&&S(e)}c=a.F?0:1;c=a.j>c?a.j:c;if(!(Date.now()>=b)){do{a:{d=a;e=c;for(var f=3;f>=e;f--)for(var h=d.g[f];h.length;){var k=h.shift(),r=d.i[k];delete d.i[k];if(r){d=r;break a}}d=null}d&&S(d)}while(d&&Date.now()<b)}a.l=!1;qa(a);a.o=ka;oa(a)&&a.start()}
g.start=function(){this.D=!1;if(0==this.h)switch(this.m=T(this),this.m){case 1:var a=this.K;this.h=this.I?window.requestIdleCallback(a,{timeout:3E3}):window.setTimeout(a,ja);break;case 2:this.h=window.setTimeout(this.M,this.N);break;case 3:this.h=window.requestAnimationFrame(this.L);break;case 4:this.h=window.setTimeout(this.J,0)}};
function U(a){if(a.h){switch(a.m){case 1:var b=a.h;a.I?window.cancelIdleCallback(b):window.clearTimeout(b);break;case 2:case 4:window.clearTimeout(a.h);break;case 3:window.cancelAnimationFrame(a.h)}a.h=0}}
g.G=function(){na(this);U(this);this.v&&document.removeEventListener("visibilitychange",this.H);H.prototype.G.call(this)};var W=u("yt.scheduler.instance.timerIdMap_")||{},ra=Q("kevlar_tuner_scheduler_soft_state_timer_ms",800),X=0,Y=0;function Z(){var a=u("ytglobal.schedulerInstanceInstance_");if(!a||a.s)a=new R(P("scheduler",void 0)||{}),w("ytglobal.schedulerInstanceInstance_",a);return a}
function sa(){var a=u("ytglobal.schedulerInstanceInstance_");a&&(a&&"function"==typeof a.dispose&&a.dispose(),w("ytglobal.schedulerInstanceInstance_",null))}
function ta(){na(Z())}
function ua(a,b,c){if(0==c||void 0===c)return c=void 0===c,-ma(Z(),a,b,c);var d=window.setTimeout(function(){var e=ma(Z(),a,b);W[d]=e},c);
return d}
function va(a){var b=Z();la(b,a)}
function wa(a){var b=Z();if(0>a)delete b.i[-a];else{var c=W[a];c?(delete b.i[c],delete W[a]):window.clearTimeout(a)}}
function xa(a){var b=u("ytcsi.tick");b&&b(a)}
function ya(){xa("jse");za()}
function za(){window.clearTimeout(X);Z().start()}
function Aa(){var a=Z();U(a);a.D=!0;window.clearTimeout(X);X=window.setTimeout(ya,ra)}
function Ba(){window.clearTimeout(Y);Y=window.setTimeout(function(){xa("jset");Ca(0)},ra)}
function Ca(a){Ba();var b=Z();b.j=a;b.start()}
function Da(a){Ba();var b=Z();b.j>a&&(b.j=a,b.start())}
function Ea(){window.clearTimeout(Y);var a=Z();a.j=0;a.start()}
;u("yt.scheduler.initialized")||(w("yt.scheduler.instance.dispose",sa),w("yt.scheduler.instance.addJob",ua),w("yt.scheduler.instance.addImmediateJob",va),w("yt.scheduler.instance.cancelJob",wa),w("yt.scheduler.instance.cancelAllJobs",ta),w("yt.scheduler.instance.start",za),w("yt.scheduler.instance.pause",Aa),w("yt.scheduler.instance.setPriorityThreshold",Ca),w("yt.scheduler.instance.enablePriorityThreshold",Da),w("yt.scheduler.instance.clearPriorityThreshold",Ea),w("yt.scheduler.initialized",!0));}).call(this);
