#include <room.h>
inherit ROOM;

void create()
{
	set("short", "�������㳡");
	set("long", @LONG
�������찲����ߵ��������ֹ㳡�������ĳ������������ͷ���죬��
�ﾩ���������ַ����ĵضΣ����ǽ�ͨҪ����Ҳ�Ǿ��ǰ����ǵľ۵�, �㳡��
��ˮ���������ַǷ���С�����ؽֽ������Լ��Ļ��һЩ���ֺ��е��˳���
�������������������������߸ߴ��ʵ�Ĺų�ǽ����������찲�Ź㳡
�ˡ��������ǿ�������������֡�
LONG );
       set("exits", ([
		"west" : __DIR__"caroad_w2",
		"east" : __DIR__"tiananmen",
	]));
	set("objects", ([
		__DIR__"npc/girl4" : 1,
		__DIR__"npc/girl2" : 1,
		__DIR__"npc/shusheng2" : 1,
	]));
	set("outdoors", "beijing");
	setup();
}

