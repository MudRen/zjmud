#include <room.h>
#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "�찲�Ź㳡");
	set("long", @LONG
��������찲�Ź㳡����ɫ�ĳ�ǽ������ׯ������֮�У�������ͨ����ˮ
�ž��ǻʹ��Ͻ����ˡ�ԶԶ��ȥ���Ͻ��ǵ������淢�Ե���ΰ�ߴ�һ������
���ƳǶ�����һ����ֱ����ʯ�����ᶫ���������Ƕ������ֹ㳡����������
�����ֹ㳡���ϱ��ǿ��������ĳ����ֹ㳡�����Ͼ���������һֱ��������̳
�������š�
LONG NOR);
	set("exits", ([
		"south" : __DIR__"cagc_s",
		"north" : __DIR__"qiao",
	       "west" : __DIR__"cagc_w",
	      "east" : __DIR__"cagc_e",
	]));
	set("objects", ([
		__DIR__"npc/maiyi2" : 1,
		__DIR__"npc/bing1" : 2,
		__DIR__"npc/old2" : 1,
		__DIR__"npc/kid1" : 1,
	]));
	set("outdoors", "beijing");
	setup();
}

