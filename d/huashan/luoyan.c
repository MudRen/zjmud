#include <room.h>
inherit ROOM;
void create()
{
	set("short", "�����");
	set("long", @LONG
�Ϸ���������壬�ǻ�ɽ��߷塣��ͷ��̼��࣬�硰̫����ͷ��������
�����족����������ǡ��ȣ����Ի���֮�ߡ��������ܣ��������¡�
LONG
	);
	set("objects", ([
		CLASS_D("huashan") + "/feng" : 1,
	]));
	set("action_list", ([
		"������":"ask feng qingyang about �ƽ�ʽ",
	]));
	set("exits", ([
		"northdown" : __DIR__"zhandao",
	]));
	set("outdoors", "huashan");
	setup();
}
