#include <room.h>
inherit ROOM;

void create()
{
	set("short", "�ش���ҩ��");
	set("long", @LONG
�ش���ҩ�����������������������������ҩ�̡��㻹û�߽��������
��һ��ŨŨ��ҩ����ζ�����Ǵ�ҩ���ϵļ��ٸ�С������ɢ�������ġ�һλ��
���ڹ�̨��վ�ţ�����Ц���к��ſ��ˡ�
LONG );
       set("exits", ([
		"west" : __DIR__"xi_2",
		"east" : __DIR__"liandan_neiting",
	]));
	set("objects", ([
		__DIR__"npc/old2" : 1,
		__DIR__"npc/kid1" : 1,
		__DIR__"npc/yaopuhuoji" : 1,
	]));
	set("outdoors", "beijing");
	setup();
}

