#include <room.h>
#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "��ˮ��");
	set("long", @LONG
һ������Ĺ��ţ�������Ͻ��ǵĻ��Ǻ�������ͨ����ˮ�����߱�����
���ǵ������ˣ������������ϣ���ʵ�ĳ�ǽ�߸ߵ������š��ŵ�������������
�찲�Ź㳡�����������������ӵ������������������е��������ﲻ������
�ַǷ���
LONG NOR);
	set("exits", ([
		"south" : __DIR__"tiananmen",
		"north" : __DIR__"hgmen_s",
	]));
	set("objects", ([
		__DIR__"npc/bing1" : 2,
		__DIR__"npc/xiaofan" : 1,
	]));
	set("outdoors", "beijing");
	setup();
}

