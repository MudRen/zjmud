// liufudayuan.c
#include <room.h>
inherit ROOM;
int do_knock(string arg);

void create()
{
	set("short", "������Ժ");
	set("long", @LONG
������Ժ�����ڼ��źܶ཭�����ͣ�ԭ�����������������ϴ�ֵ�
�����ӡ�����ү���ں�����Ե�ܺã�����������Ȼ���٣���Ժ���Ѱ���
�ܶ������ӣ������������������֡�
LONG);
	set("exits", ([
	    "north"  : __DIR__"liufudating",
	    "south"    : __DIR__"liufugate",
	]));
	set("objects", ([
		"/d/taishan/npc/dao-ke" : 1,
		"/d/taishan/npc/jian-ke" : 1,
		"/d/huashan/npc/haoke" : 1,
	]));
	setup();
}
