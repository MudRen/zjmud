#include <room.h>
inherit ROOM;

void create()
{
	set("short", "�ض����");
	set("long", @LONG
�����Ǳ����ǵذ��ŵĶ��֡��ֵ�����������������֣������������ﲻ
����������ƥ�������С���������й�����ˣ��Ͼ��Ͽ��Ŀ����������ŵ���
�������Լ�������ˣ�ŵ���ͯ������һ����æ���ֵ�ʢ�����󡣱����Ǿ��ǹ�
�Ӽ�����ڵء��ϱ��ǵذ��ŵĶ��ֹ㳡��
LONG );
       set("exits", ([
		"north" : __DIR__"guozijian",
		"south" : __DIR__"di_donggc",
		"east" : __DIR__"dong_3",
		"west" : __DIR__"di_dajie1",
	]));
	set("objects", ([
		__DIR__"npc/bing2" : 1,
		__DIR__"npc/taijian" : 1,
	]));
	set("outdoors", "beijing");
	setup();
}

