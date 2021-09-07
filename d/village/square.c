// Room: /d/village/square.c	 
inherit ROOM; 
	
void create() 
{ 
	set("short", "��ȳ�"); 
	set("long", @LONG 
�����Ǵ��ӵ����ģ�һ��ƽ̹�Ĺ㳡��ÿ�����մ�Ⱦ����⡣�㳡�� 
���пô�����ƽ�ղ��෹�ᣬ�������Ů���ٶ�����������̸��˵�ء�      
LONG 
	); 
	set("exits", ([ /* sizeof() == 3 */ 
		"northwest" : __DIR__"nwroad2", 
		"south" : __DIR__"sroad4", 
		"east"  : __DIR__"eroad3", 
	])); 
	set("objects", ([ 
		__DIR__"npc/kid": 2, 
		"/clone/npc/walker" : 1, 
	]));	
	set("outdoors", "village"); 
	setup(); 
} 
