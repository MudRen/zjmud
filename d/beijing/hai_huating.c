inherit ROOM;
#include <ansi.h>

void create()
{
	set("short","����");
	set("long", @LONG
��������ǺȾ����µļ�����һ��Сͤ�ӽ������������룬����Χ����һ
Щ�����١�һ��΢�紵�����������ƺ��������Ļ���Ʈ������������
LONG );
	set("exits", ([
		"west" : __DIR__"hai_dayuan",
	]));

	setup();
}
