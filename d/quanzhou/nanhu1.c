// Room: /d/quanzhou/nanhu1.c
// Date: May 21, 96   Jay

#include <ansi.h>

inherit BUILD_ROOM;

void create()
{
	set("short", "�����Ϻ�");
	set("long", @LONG
�������̲������Ϻ������ϼ�ֻ�������ε������ϵ��οͺ���
¥Ů������Ц����ˮ���û�д��Ƕɲ���ȥ�ġ�����֪��˭�ں���
����һЩľ׮��׮��Ǳ��ˮ��֮��һ����ĵط�����ʹ�ǲ����Ṧ��
������ȥҲ����ˮ��Ư�����ӡ�
LONG );
	set("max_room", 1);
	set("exits", ([
		"south"     : __DIR__"yanyu",
		"northwest" : __DIR__ "nanhu",
	]));
	set("outdoors", "jiaxing");
	setup();
	replace_program(BUILD_ROOM);
}
