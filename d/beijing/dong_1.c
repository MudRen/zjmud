#include <room.h>
inherit ROOM;

void create()
{
	set("short", "�ض����");
	set("long", @LONG
�����Ǳ����ǵذ��ŵĶ��֡��ֵ�����������������֣������������ﲻ
����������ƥ�������С���������й�����ˣ��Ͼ��Ͽ��Ŀ����������ŵ���
�������Լ�������ˣ�ŵ���ͯ������һ����æ���ֵ�ʢ�����󡣱����ǵذ���
���ֵĹ㳡���ϱ߾������ϣ���ʱ�йٱ�����������ԭ��������Ǿ��ǵ�����
���������Ĵ������ڵء���������������������֡�
LONG );
       set("exits", ([
		"north" : __DIR__"di_donggc",
		"east" : __DIR__"wang_7",
		"south" : __DIR__"dongchang_men",
	]));
	set("objects", ([
		__DIR__"npc/bing2" : 1,
		__DIR__"npc/taijian" : 1,
	]));
	set("outdoors", "beijing");
	setup();
}

