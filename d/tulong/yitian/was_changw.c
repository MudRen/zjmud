#include <ansi.h>

inherit ROOM;

void create()
{
	set("short", "ͥԺ");
	set("long", @LONG
���������µ���Ժ����ɨ�÷ǳ��ɾ�����Ժ�����Ǽ�����ݣ�ȫ����
ľ��ɣ������ľ����ľ�Ͼ���ȥƤ����Ȼ���ӣ�ȴ���Ժ���Ե�һ�����
�Ի͵ĵ��ý�Ȼ��ͬ�����ﵽ�������ɹű����䱸�������ϡ�
LONG );
	set("exits", ([
		"east" : __DIR__"was_dayuan",
	]));

	set("objects", ([
		__DIR__"npc/bing1" : 5,
	]));

	set("outdoors", "beijing");
	setup();
}


