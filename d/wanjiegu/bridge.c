// Room: /t/wanjiegu/bridge.c

#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "������");
	set("long", @LONG
һ��������׽��������ţ����Ź����ĵ��������������£���
��ľ�壬�Թ����ߣ��������ԣ���Ϊ���֡�һ̤���ţ�����������
���ζ�����ˮ������������ڴӽŵ׷ɹ���ֻҪһ��ʧ�㣬����
��ˮ�������õ�ˮ��Ҳ�ѻ�����
LONG
	);
	set("outdoors", "wanjiegu");
	set("exits", ([ /* sizeof() == 2 */
	    "west" : __DIR__"port2",
	    "east" : __DIR__"port",
	]));

	setup();
}

