// Room: /d/quanzhou/zhongxin.c
// Date: May 7, 96   Jay

inherit ROOM;

void create()
{
	set("short", "������");
	set("long", @LONG
Ȫ����һ�������ĸ۳ǡ���Ȼ�����ǳ����ģ�����Ҳֻ�ǽŲ������
����������������������һ���ۿڣ���������Գ�����������һ��С�
LONG );
	set("exits", ([
		"north" : __DIR__"beimen",
		"south" : __DIR__"nanmen",
		"east"  : __DIR__"haigang",
		"west"  : __DIR__"ximen",
		"southeast" : __DIR__"majiu1",
	]));
	set("outdoors", "quanzhou");
	setup();
}

