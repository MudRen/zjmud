//ROOM: /d/yanziwu/shijian.c

inherit ROOM;

void create()
{
	set("short", "�Խ�̨");
	set("long",@LONG
��ʯ����Χ�ɵ�һ��ʯ̨��Ľ�����ҵĵ��Ӿ����ڴ���ϰ�似��̨
�Ƿ��ŵ�ǹ��ꪵ�ʮ�˰������ ��������һЩ������Ϊ�����ľ�ˡ�
��������Ľ�ݼҵ��ӿ������еĵط���
LONG );
	set("outdoors", "yanziwu");
	set("exits", ([
		"south"  : __DIR__"changlang",
		"east"   : __DIR__"kuxiu",
	]));

	set("objects", ([
		"/clone/npc/mu-ren" : 4,
		"/clone/weapon/zhubang.c" : 1,
		"/clone/weapon/mudao.c"   : 1,
		"/clone/weapon/zhujian.c" : 1,
		"/clone/weapon/bian.c"    : 1,
	]));
	set("for_family", "Ľ������");

	setup();
}
