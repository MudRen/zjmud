#include <room.h>
inherit ROOM;

void create()
{
	set("short", "������");
	set("long", @LONG
��������һ���ź�綫�������ţ��������������У��������ӻ������Ϸ��
�ܽ����������˵Ⱦ۾ӵ����ڡ������Ĵ�����ϱ���ͷ���졣���Ϸ���ֱ����
���Ե��ﱱ���������ʤ��̳��������һ������Ŀյأ�����������ֵĳ���
�ֹ㳡�ˡ������ŵĶ�����������ֱ������˾��ǵ����ڶ��ֺͻ���·��
LONG );
	set("exits", ([
		"south" : __DIR__"tiantan_n",
		"north" : __DIR__"cagc_s",
		"east" : __DIR__"yong_1",
		"west" : __DIR__"fu_2",
	]));
	set("objects", ([
		__DIR__"npc/maiyi2" : 1,
		__DIR__"npc/xianren" : 2,
		__DIR__"npc/xiaofan" : 1,
		__DIR__"npc/old1" : 1,
		__DIR__"npc/boy2" : 1,
	]));
	set("outdoors", "beijing");
	setup();
}

