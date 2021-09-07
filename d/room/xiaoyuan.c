// xiaoyuan.c

inherit ROOM;

static mapping room_type = ([
	"dule"    : "���־�",
	"caihong" : "�ʺ��",
	"panlong" : "������",
]);

void create()
{
	object ob;

	set("short", "СԺ");
	set("long", @LONG
������һ�������Ժ�ӣ������ڷ���ľ��ש�ߡ�Ժ������һ���ˣ���
��Ʈ�����ľ��ڽ�֮�硣����Χ�ż������ӣ�ר����־������ʦ���Ρ�Ժ
�ǵ�һ�����Ϲ���һ�����ӣ����飺�������ַ��ݣ������߾�����³��Ǣ
̸��
LONG );
	set("exits", ([
		"west"  : "/d/shaolin/yidao2",
		"dule"  : __DIR__"dule/xiaoyuan",
		"caihong" : __DIR__"caihong/xiaoyuan",
		"panlong" : __DIR__"panlong/dayuan",
	]));

	set("outdoors", "city");

	set("objects", ([
		__DIR__"npc/jinlin" : 1,
	]));

	set("no_fight", 1);
	set("no_sleep_room", 1);

	setup();
	"/adm/npc/luban"->come_here();
}

string query_room_id(string arg)
{
	if (arg && ! undefinedp(room_type[arg]))
		return room_type[arg];

	return 0;
}

void reset()
{
	::reset();
	"/adm/npc/luban"->come_here();
}

