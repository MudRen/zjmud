// Room: /d/xiakedao/xkroad4.c
inherit ROOM;

void create()
{
	set("short", "�Ϻ����");
	set("long", @LONG
�����Ϻ��ذ���ƫƧС�壬ϡϡ����ļ����˼ҡ��յ������ż�
��������������ǲ��κ����Ϻ��ˡ������ߺ����и���ۡ�����
��С���ɳ̲ɹ������
LONG );
	set("outdoors", "nanhai");
	set("exits", ([
		"north"   : __DIR__"xkroad3",
		"south"   : __DIR__"haibin",
		"east"    : __DIR__"xkroad5",
		"west"    : __DIR__"haigang",
	]));
	setup();
}

