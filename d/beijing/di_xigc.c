#include <room.h>
inherit ROOM;

void create()
{
	set("short", "�ذ������ֹ㳡");
	set("long", @LONG
�����ǵذ��ŵ����ֵĹ㳡���ذ��Ŷ����������ͷ���죬����Ҳ������
�ķ����ضΣ��Ǿ��Ǳ��ߵĽ�ͨҪ�����㳡�����ַǷ���С�����ؽֽ�������
���Ļ������Ҳ����������һЩ��å��졣�ϱ��Ǿ��ǵ����������������
�ڵء����߾��ǵذ��Ź㳡�ˡ�
LONG );
       set("exits", ([
		"north" : __DIR__"di_5",
		"south" : __DIR__"di_2",
		"east" : __DIR__"dianmen",
		"west" : __DIR__"di_3",
	]));
	set("objects", ([
		__DIR__"npc/xianren" : 1,
		__DIR__"npc/hunhun" : 1,
	]));
	set("outdoors", "beijing");
	setup();
}

