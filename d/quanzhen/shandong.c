// shantong.c ��ɽɽ��
#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "��ɽɽ��");
	set("long", @LONG
������ȫ��̿�ɽ��ʦ���������˾��޵�ɽ���������󣬵�
���沼�õú����£�����˼ҵĿ���һ���������Ϲ���һ����
(hua)�����β輸���ܾ��¡�
LONG
	);
	set("exits", ([
		"out" : __DIR__"xiaolu12",
	]));
	set("item_desc", ([
	"������": "������һ�������ʿ�ı�Ӱ��������ʲô��ò��������һ��ָ�죬�������š�"+MAG"��������"NOR+"���������֡�\n"
	]) );

	set("objects", ([
		CLASS_D("quanzhen") + "/wang" : 1,
	]));

	setup();
}

