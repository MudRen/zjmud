#include <room.h>
inherit ROOM;

void create()
{
	set("short", "��Ժ");
	set("long", @LONG
һ���Ӳݴ������ĺ�ԺԺ�ӣ���Ժ������һ��������ĺ�ͬ�������Ǽ���
���ݣ�����Ҳ����ô�ƾɡ�Ժ�к������˵ĵ���һЩʯ����������Ѱ�����ս�
���õ����ġ�һ������վ�ڴ�Ժ�����У����ӵ����Ķ����㡣
LONG );
       set("exits", ([
		"north" : __DIR__"qingmu_men",
		"south" : __DIR__"qingmu_fang2",
		"east" : __DIR__"qingmu_fang1",
		"west" : __DIR__"qingmu_fang3",
	]));
	set("objects", ([
		CLASS_D("yunlong") + "/xuanzhen" : 1
	]));
	set("outdoors", "beijing");
	setup();
}

