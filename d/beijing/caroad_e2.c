#include <room.h>
inherit ROOM;

void create()
{
	set("short", "��������");
	set("long", @LONG
���ֵĶ�����������Ͻ��ǵĽ�ͨҪ������������ʯ���������ͷ���죬
�ֵ������˲��ϣ�������ʢ�������Զ��������������ԶԶ����������һ��
�¸ߴ��ʵ�Ĺų�ǽ�������������찲�Ź㳡�ˡ������Ǿ�����Ϊ�������ֵ�
��������֡����ϱߴ���һ��Ũ�ҵ��̲���ζ��ԭ��������һ���̲ݵꡣ����
��һ���ӻ��̡�
LONG );
       set("exits", ([
		"north" : __DIR__"wang_2",
		"south" : __DIR__"yancao",
		"east" : __DIR__"zahuo",
		"west" : __DIR__"caroad_e1",
	]));
	set("objects", ([
		__DIR__"npc/old1" : 1,
		__DIR__"npc/hunhun" : 1,
	]));
	set("outdoors", "beijing");
	setup();
}

