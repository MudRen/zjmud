// Room: /d/xiakedao/xiaodian.c
inherit ROOM;

void create()
{
	set("short", "С�Ե�");
	set("long", @LONG
���С�Ե겼�ü��ף��տյ�ʯ��ʲôҲû�У�������ȴ�ܺá�
�˿Ͷ��ǴҴҵĽ����ˣ������ӡ����ȡ��׾ƾ͸�·ȥ�ˡ�
LONG );
	set("exits", ([
		"west" : __DIR__"yingbin",
	]));
	set("objects", ([
		__DIR__"npc/xiaoer2" : 1,
	]));
	setup();
}

