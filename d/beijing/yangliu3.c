#include <room.h>
inherit ROOM;

void create()
{
	set("short", "������ͬ");
	set("long", @LONG
������������ͬ�ĵ׶ˣ��ߵ���������Ѿ�������ˡ�һ·�ϣ���ͬ��
���ĺ�Ժ�Ĵ��Ž����ţ�Ψ�������ϱߵ�һ���ĺ�Ժ�����ǳ����ŵġ��㲻��
��ȥ��һ����
LONG );
       set("exits", ([
		"north" : __DIR__"yangliu2",
		"south" : __DIR__"qingmu_men",
	]));

	set("outdoors", "beijing");
	setup();
}

