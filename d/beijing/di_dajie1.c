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
		"north" : __DIR__"di_dajie2",
		"south" : __DIR__"dianmen",
		"east" : __DIR__"dong_2",
		"west" : __DIR__"di_5",
	]));

	set("outdoors", "beijing");
	setup();
}

