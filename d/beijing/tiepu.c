#include <room.h>
inherit ROOM;

void create()
{
	set("short", "������");
	set("long", @LONG
�������ڶ��ֵ�һ�Ҽ�ª�Ĵ����̣����İ���һ����¯��¯��������յ�
һƬͨ�죬��һ�߽�ȥ�͸е�������ȡ������̵�ǽ�Ƕ��������깤��δ�깤
�Ĳ˵���������������ذ�ס����׵��һλ������ͷ�󺹻�����������ר��
��־���ڴ�����
LONG );
       set("exits", ([
		"north" : __DIR__"yong_2",
	]));
	set("objects", ([
		__DIR__"npc/tiehuoji" : 1,
		__DIR__"npc/tiejiang" : 1,
	]));
	set("outdoors", "beijing");
	setup();
}

