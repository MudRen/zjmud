#include <room.h>
inherit ROOM;

void create()
{
	set("short", "�������");
	set("long", @LONG
�����Ǳ����ǵذ��ŵ����֡��ֵ�����������������֣������������ﲻ
����������ƥ�������С���������й�����ˣ��Ͼ��Ͽ��Ŀ����������ŵ���
�������Լ�������ˣ�ŵ���ͯ������һ����æ���ֵ�ʢ�����󡣴�����һֱ��
�����Ե��ﵱ����һ�����ݵĸ�ۡ�����Ͼ�����������ֿ���ͨ��������
LONG );
       set("exits", ([
		"north" : __DIR__"di_3",
		"east" : __DIR__"di_2",
		"south" : __DIR__"bei_4",
	]));
	set("objects", ([
		__DIR__"npc/youren" : 1,
		__DIR__"npc/shusheng2" : 1,
		__DIR__"npc/kid1" : 1,
	]));
	set("outdoors", "beijing");
	setup();
}

