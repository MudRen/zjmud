#include <room.h>
#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "�ذ��Ź㳡");
	set("long", @LONG
������ǵذ��Ź㳡����ɫ�ĳ�ǽ������ׯ������֮�У�����ͨ���Ͻ���
�ĵذ��ž��ǳǽ��ˡ�ԶԶ��ȥ���Ͻ��ǵ������淢�Ե���ΰ�ߴ�һ������
���ƳǶ�����һ����ֱ����ʯ�����ᶫ���������ǵذ��Ŷ��ֹ㳡��������
�ذ������ֹ㳡���ϱ�ͨ��һ��С�ž��ǻʹ��ı����ˡ�
LONG NOR);
	set("exits", ([
		"south" : __DIR__"hgmen_n",
		"north" : __DIR__"di_dajie1",
	       "west" : __DIR__"di_xigc",
	      "east" : __DIR__"di_donggc",
	]));
	set("objects", ([
		__DIR__"npc/bing1" : 2,
		__DIR__"npc/bing3" : 1,
		__DIR__"npc/old2" : 1,
		__DIR__"npc/kid1" : 1,
	]));
	set("outdoors", "beijing");
	setup();
}

