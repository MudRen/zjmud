#include <room.h>
inherit ROOM;

void create()
{
	set("short", "�������鷿");
	set("long", @LONG
�����ǿ������鷿�������������������ضѷ��źܶ��顣�������ϻ���
һЩ�ҳ�����Ȼ�Ǻܾ�û�ж����ˡ��������ļ�����������ȴ���Ե�������
͸��������ˡ�
LONG );
	set("exits", ([
		"south" : __DIR__"kangfu_zoulang2",
	]));

	set("outdoors", "beijing");
	setup();
}
