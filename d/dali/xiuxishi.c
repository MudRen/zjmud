//Room: /d/dali/xiuxishi.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
	set("short", "�᷿");
	set("long", @LONG
���Ǽ�������᷿�����Ŵ������ţ����ߺܻ谵������������
ֻ���м���ż�����ʰ����������Ĵ󴲣����ž�������˯��������
����Ϣ�ĵط�����ʱ���������ˣ��μҵ���Ҳ����������Ϣ��
LONG);
	set("exits",([ /* sizeof() == 1 */
	    "north"  : __DIR__"chahua1",
	]));
	set("sleep_room", 1);
	set("no_fight", 1);
	setup();
}
