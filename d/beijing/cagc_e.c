#include <room.h>
inherit ROOM;

void create()
{
	set("short", "�������㳡");
	set("long", @LONG
�������찲���ұߵĶ������ֹ㳡�������ĳ������������ͷ���죬��
�ﾩ���������ַ����ĵضΣ����ǽ�ͨҪ����Ҳ�Ǿ��ǰ����ǵľ۵�, �㳡��
��ˮ���������ַǷ���С�����ؽֽ������Լ��Ļ��һЩ���ֺ��е��˳���
�������������������������߸ߴ��ʵ�Ĺų�ǽ����������찲�Ź㳡
�ˡ��������Ƕ�������֡�
LONG );
       set("exits", ([
		"east" : __DIR__"caroad_e1",
		"west" : __DIR__"tiananmen",
	]));
	set("objects", ([
		__DIR__"npc/shusheng1" : 2,
		__DIR__"npc/xianren" : 1,
	]));
	set("outdoors", "beijing");
	setup();
}

