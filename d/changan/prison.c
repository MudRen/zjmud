// by ranger_����
// Prison.c

inherit ROOM;

void create()
{
	set("short", "����");
	set("long", "����ں����ģ����ϵ�é��Ҳ��ʪ�����ģ�����е���������������ڼ����������ڵ����ӣ���������������ѹ���");
	set("no_fight","1");
	set("action_list",([
		"�������":"maitong",
		"�鿴ʱ��":"ptime",
	]));
	setup();
}

void init()
{
	add_action("cha_ptime","ptime");
	add_action("maitong_yuzu","maitong");
}

int maitong_yuzu(string arg)
{
	int cost,num;
	string type,str;
	object me = this_player();

	num = me->query_time_to_leave()/10;
	if(!arg)
	{
		str = ZJOBLONG"��Ҫ���ֽ��Ǵ�������䣿\n";
		str += ZJOBACTS2+ZJMENUF(3,3,10,30);
		str += "�ֽ���:maitong �ֽ�";
		str += ZJSEP"�����:maitong ���";
		tell_object(me,str+"\n");
		return 1;
	}
	else if(sscanf(arg,"%s %d",type,cost)!=2)
	{
		if(arg != "�ֽ�" && arg != "���")
		{
			tell_object(me,"�����ʽ����\n");
			return 1;
		}
		str = INPUTTXT("����"+num+"�ƽ������¿���ֱ�ӷ����ȥ���뻨�Ѷ��ٽ�ҵ�"+arg+"��¸���䣿","maitong "+arg+" $txt#\n");
		str += ZJOBACTS2+ZJMENUF(3,3,10,30);
		str += "ֱ����ͨ:maitong "+arg+" 0";
		tell_object(me,str+"\n");
		return 1;
	}

	if(cost == 0) cost = num;

	if(cost < 10)
	{
		tell_object(me,"����Ҳ��10����Ҳ��õó��ְɣ�\n");
		return 1;
	}

	if(type == "���")
	{
		if(me->query("balance")<cost*10000)
		{
			tell_object(me,"��Ǯׯ�Ĵ��û��ô��Ǯ��\n");
			return 1;
		}
		me->add("balance",-cost*10000);
	}
	else if(type == "�ֽ�")
	{
		if(!MONEY_D->player_pay(me,cost*10000))
		{
			tell_object(me,"������û����ô��Ǯ��\n");
			return 1;
		}
	}
	else
	{
		tell_object(me,"�����ʽ����\n");
		return 1;
	}

	tell_object(me,HIG"����"+cost+"��һ�¸�����䣡"NOR"\n");
	log_file("pay/prison", sprintf("%s:%s(%s)��%d�ƽ��¸�����䡣\n",ctime(time()),me->query("name"),me->query("id"),num));
	if(cost==num)
	{
		me->leave_prison(0,0);
	}
	else
	{
		tell_object(me,HIG"�������ʱ��������"+cost/6+"���ӣ�"NOR"\n");
		me->leave_prison(0,cost/6);
	}
	return 1;
}

int cha_ptime()
{
	if(this_player()->query_time_to_leave()>1)
		tell_object(this_player(),"�㻹��"HIR+appromix_time(this_player()->query_time_to_leave(), 1)+NOR"���ܳ�ȥ��\n");
	else
		tell_object(this_player(),HIG"�����Ͼ��ܳ�ȥ�ˣ��𼱡�"NOR"\n");
	return 1;
}

int free_ob(object me)
{
	string startroom;
	message_vision("����������������˳���������$N���������ˣ���������ˣ�Ҫ���ٸҷ������ߺ�...\n\n", me);
	message("vision", "���������" + me->name() +"���˳�ȥ... �㲻��̾��һ������\n",environment(me), ({ me }));

	tell_object(me, HIR "�㱻��������������˳�����..."NOR"\n");

	if (me->is_ghost())
		startroom = "/d/death/gate";
	else
		startroom = "/d/changan/baihu1";

	me->set("startroom", startroom);
	me->move(startroom);
	message("vision", "�����������һ���㲵�" + me->name() + "���˳������򿪼���������һ���ͻ�ȥ�ˡ�\n",environment(me), ({ me }));
	return 1;
}

void catch_back(object me)
{
	message_vision(HIM "��Ȼ����������˹���������Χס$N"HIM "����һ��ʹŹ���ߴ����������üһ��������...��"NOR"\n", me);

	message("vision", HIY "��Ⱥ�����" + me->name() + HIY "��û�����ȥ��Ȼ�����ϼ���Ѻ���ˡ�"NOR"\n",environment(me), ({ me }));
}

void catch_ob(object me)
{
	message_vision(HIM "��Ȼ�����ظ��˹�����һ��ץס$N����������ס����ݺݵĽе�����վס���㷸���ˣ�������߰ɣ���"NOR"\n",me);

	message("vision", HIY "��������ȭ���Ű�" + me->name() +	"���������ˡ�"NOR"\n",environment(me), ({ me }));
}
