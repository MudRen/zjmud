// Room: /city/yamen.c
// YZC 1995/12/04 

inherit ROOM;

void create()
{
	set("short", "���Ŵ���");
	set("long", @LONG
���������Ŵ��ţ�������ľ���Ž����ر��š����ྲ�����رܡ������ӷ�
����ͷʯʨ�ӵ��Աߡ�ǰ����һ����ģ���Ȼ�ǹ�С����ԩ�õġ�������������ǰ
Ѳ�ߡ�
LONG );
	set("exits", ([
		"south" : __DIR__"xidajie1",
		"north" : __DIR__"ymzhengting",
	]));
	set("objects", ([
		__DIR__"npc/yayi" : 4,
	]));
	set("action_list", ([
		HIY"����ͨ��"NOR:"xuanshang",
	]));
	setup();
}

void init()
{
	add_action("xuanshang","xuanshang");
}

int xuanshang(string arg)
{
	string str,msg;
	int money,i;
	object *ob,killer,me = this_player();

	if(!arg)
	{
		ob = filter_array(users(),(: $1->query_condition("killer")>0 :));
		if(!sizeof(ob))
			return notify_fail("Ŀǰû�п�����ͨ���Ķ���\n");

		str = ZJOBLONG"��ѡ����Ҫ����ͨ���Ķ���\n"ZJOBACTS2+ZJMENUF(1,1,10,30);
		for (i = 0; i < sizeof(ob); i++)
		{
			str += (ob[i]->name()+"("+ob[i]->query("id")+")��ͨ��ʱ�䣺"+ ob[i]->query_condition("killer")/30 + "���ӡ�:xuanshang "+ob[i]);
			if(i<(sizeof(ob)-1)) str += ZJSEP;
		}
		tell_object(me,str+"\n");
		return 1;
	}

	if(sscanf(arg,"%s %d",arg,money)!=2)
	{
		if(!objectp(killer=find_player(arg)))
			return notify_fail("��Ҫͨ������˭��\n");
		if(!killer->query_condition("killer"))
			return notify_fail("�����Ŀǰû��ͨ�������ܱ����ͣ�\n");
		tell_object(me,INPUTTXT("�����ö��ٽ������"+killer->name()+"("+killer->query("id")+")"ZJBR"(1-1000��1���ƽ�20��ͨ��ʱ�䣬ͨ��ʱ�䳬��150���ӻ�ֱ�ӱ�ץ������)��","xuanshang "+arg+" $txt#")+"\n");
		return 1;
	}

	if(!objectp(killer=find_player(arg)))
		return notify_fail("��Ҫͨ������˭��\n");
	if(!killer->query_condition("killer"))
		return notify_fail("�����Ŀǰû��ͨ�������ܱ����ͣ�\n");
	if(money>1000||money<1)
		return notify_fail("������1-1000��\n");

	if(me->query("balance")<money*10000)
	{
		tell_object(me,ZJOBLONG"��Ǯׯ��û����ô��Ļƽ�ȥ�����ˣ�\n");
		return 1;
	}
	me->add("balance",-money*10000);
	killer->apply_condition("killer",killer->query_condition("killer")+money*10);
	tell_object(me,ZJOBLONG"���ͳɹ����ٸ��ӳ��˶�"+killer->query("name")+"��ͨ��ʱ�䣡\n");
	tell_object(me,HIC"�������俴����ӲӵĻƽ�ü����Ц�Ķ���˵�����İɣ�ֻҪ���˱��������ұ�֤�������ε�������"NOR"\n");
	CHANNEL_D->do_channel(this_object(), "rumor", "��˵�����ؽ����˹ٸ����£���ͷ���ظ���֤Ҫ��"+killer->query("name")+"���ε�������");

	return 1;
}

int valid_leave(object me, string dir)
{
	if (!wizardp(me) && objectp(present("ya yi", environment(me))) && dir == "north")
		return notify_fail("���ۺȵ������������䡭������\n");
	return ::valid_leave(me, dir);
}
