#include <room.h>
inherit ROOM;

void create()
{
	set("short", "�ذ��Ŵ��");
	set("long", @LONG
�����Ǳ����ǵĵذ��Ŵ�֡��ֵ�����������������֣������������ﲻ
����������ƥ�������С���������й�����ˣ��Ͼ��Ͽ��Ŀ����������ŵ���
�������Լ�������ˣ�ŵ���ͯ������һ����æ���ֵ�ʢ�����󡣱��߹��ذ���
���ﾩ�ǵĳǽ����ϱ������ֵĵذ��Ź㳡��
LONG );
       set("exits", ([
		"north" : __DIR__"di_anmen",
		"south" : __DIR__"di_dajie1",
	]));
	set("objects", ([
		__DIR__"npc/dipi" : 1,
		__DIR__"npc/tiaofu" : 2,
	]));

	set("outdoors", "beijing");
	setup();
}

