#include <room.h>
inherit ROOM;

void create()
{
	set("short", "�ʻ���");
	set("long", @LONG
����һ��СС�ĵ��棬��˵������ϰ��Ǹ���ʮ�������ͷ�ӣ��������
ʱ������ȴ��һλ��������С�����ʱ������ϸ�ĵ�Ϊ�ͻ���ѡ���䣬̬
�ȷǳ�����, ���ϵ�����С������ʢ������������Ц�ݡ���ʱ��Ҳ��ո�Ȥ��
���������������
LONG );
       set("exits", ([
		"south" : __DIR__"yong_2",
	]));
	set("objects", ([
		__DIR__"npc/huanv" : 1,
	]));
	set("outdoors", "beijing");
	setup();
}

