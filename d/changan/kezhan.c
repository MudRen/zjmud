//Room: kezhan.c

inherit ROOM;

void create ()
{
	set ("short", "�ñ���ջ");
	set ("long", @LONG
��ҿ�ջ�����������ģ����Ŀ�ջ��Ҳ�ǻ�Ǯ�Ŀ�ջ������
ס�����ջ�ֻҪ�����㹻��Ǯ�������ò����߳���ջ���ţ��Ϳ���
���һ����õ����ܡ������ֻҪ�㿪�ڣ������˻Ὣ�����������
�Ĳˣ�������ĸ�ˣ�������Ů���͵�����������ǽ�Ϲ���һ�����ӡ�
LONG);
	set("exits", ([ /* sizeof() == 2 */
		"north" : __DIR__"qixiang1",
		"up": __DIR__"kzsleep",
	]));
	set("objects", ([ /* sizeof() == 1 */
		__DIR__"npc/xiaoer" : 1,
	]));
	set("no_fight", 1);
	set("no_magic", 1);
	set("resource", ([ /* sizeof() == 1 */
	"water" : 1,
	]));

	setup();
}

int valid_leave(object me, string dir)
{
	if (!me->query_temp("rent_paid") && dir == "up" )
		return notify_fail("��С��������Ц�ص�ס���㣺�Բ��������ǿ��˵��Է������Ǳ���Ŀ��ˣ�������ȥ��\n");
	return ::valid_leave(me, dir);
}
