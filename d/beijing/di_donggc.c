#include <room.h>
inherit ROOM;
void create()
{
	set("short", "�ض��㳡");
	set("long", @LONG
�����ǵذ��ŵĶ��ֵĹ㳡���ذ��Ŷ����������ͷ���죬����Ҳ������
�ķ����ضΣ��Ǿ��Ǳ��ߵĽ�ͨҪ�����㳡�����ַǷ���С�����ؽֽ�������
���Ļ������Ҳ����������һЩ��å��졣�ϱ��Ǿ��ǵ����������������
�ڵء������ǵذ��Ź㳡�����߽Ӿ�����������������֡�
LONG );
       set("exits", ([
		"north" : __DIR__"dong_2",
		"south" : __DIR__"dong_1",
		"east" : __DIR__"wang_9",
		"west" : __DIR__"dianmen",
	]));
	set("objects", ([
		__DIR__"npc/liumang" : 1,
		__DIR__"npc/kid1" : 1,
		__DIR__"npc/girl2" : 1,
	]));
	set("outdoors", "beijing");
	setup();
}

