// Room: /d/huashan/sgyhole.c

inherit ROOM;

void create()
{
	set("short", "ɽ��");
	set("long", @LONG
����һ���������۵�ɽ�������������ʯ����ȴ��������������������
��ʧ���ľ�����С�������ʯ��(wall)�Ϻܶ�С�ˣ�ȫ�����������ƣ����
��������֮������ʮ�����
LONG );
	set("exits", ([ /* sizeof() == 4 */
	    "southup" : __DIR__"zhandao",
	    "out"     : __DIR__"sgyhole1",
	]));
	set("item_desc", ([ 
	    "wall" : @TEXT

       o    | o      o    \ o      o      o     <o     <o>
    --^|\    ^|^  --v|^    v|v    |/v   \|X|    \|      |
       /\     >\    /<      >\    /<      >\    /<      >\

       o>     o      o      o      o      o      o      o
       \ __   x     </     <|>    </>    <\>    <)>     |\__
      /<      >\    /<      >\    /<      >\     >>     L
TEXT
	]));

	setup();
}
void init()
{
	add_action("do_mianbi", "mianbi");
}

int do_mianbi()
{
	object ob;
	int c_skill;

	ob = this_player();

	c_skill = (int)ob->query_skill("sword", 1);
	if (c_skill < 20)
	{
		message_vision("$N�Խ������˽���Ȼ̫�ͣ���"
			       "������ʯ�����ݡ�\n", ob);
		return 1; 
	}

	if (! ob->can_improve_skill("sword"))
	{
		message_vision("$N��ʵս���鲻�㣬�޷�����"
			       "ʯ�����ݡ�\n", ob);
		return 1; 
	}

	if (ob->query("jing")<20)
	{
		message_vision("$N̫���ˣ������޷�����ʯ�����ݡ�\n",ob);
		return 1; 
	}

	if (c_skill >= 100)
	{
		message_vision("$N����ʯ������̫��ǳ�ˡ�\n", ob);
		return 1;
	}

	message_vision("$N�����ʯ��������˼�����ã��Ի���"
		       "������������\n", ob);
	ob->improve_skill("sword", 1 + random(ob->query("int")));
	ob->receive_damage("jing", 15);
	return 1;
}
