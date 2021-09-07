
string *no_kill_list = ({
	"mu ren", "jin ren", "yin ren", "zhong shentong", "zhu cong", "shi ren", "huo du","he shiwo"
});

string *target_list = ({
	"/d/xiangyang/biaoju",
	"/d/beijing/haibin",
});

int do_accept(string arg)
{
	object ob, cart, biaotou, target, *living;
	object me, *team, maxplayer, place;
	int totalexp=0, maxexp, minexp;
	int i, j, teams,times;
	string endname, str;
        mixed *local,*last;

        local = localtime(time() * 60);
	me = this_player();

	if (arg != "quest") return 0;

	if (sizeof(filter_array(children(__DIR__"obj/cart"), (: clonep :))) > 4) {
		command("say ���������Ѿ����˽�����֧���ˡ�");
		return 1;
	}

	team = me->query_team();
	if (sizeof(team) < 2 ){
		command("say ����·;Σ�գ�����ô�ٵ��ˣ��ҿɲ����ġ�");
		return 1;
	}
	else if(sizeof(team) > 4){
		command("say ����·;Σ�գ������˶���û�õġ�");
		return 1;
	}
	if ( team[0] != me) {
		command("say ֻ�ж����������������ڡ�");
		return 1;
	}
	for (i=0;i<sizeof(team);i++){
		if (!team[i]){
			command("say ��Ķ�����������⣬���ɢ�������齨��");
			return 1;
		}
		if (team[i]->query_temp("protecting")) {
			command("say �ţ���Ķ�������ô�����̰��֮�ˣ�");
			return 1;
		}
		if( team[i]->query_temp("quest/busy")) //added by tangfeng ��quest��ͻ
		{
			command("say ���������ڽ���֮�У����ǻ����ȴ����������������˵�ɡ�");
			return 1;
		}
		if (!present(team[i],environment(this_object()))){
			command("say �ף���ô�����˲�ȫ����"+team[i]->query("name")+"��ôû����");
			return 1;
		}
		if(team[i]->query("day_jobs/hubiao/last_time"))
		{
			last = localtime(team[i]->query("day_jobs/hubiao/last_time"));
			times = team[i]->query("day_jobs/hubiao/times");

			if(last[7]!=localtime(time())[7])
				team[i]->set("day_jobs/hubiao/times",0);
			else if(last[7]==localtime(time())[7]&&times>=5)
			{
				command("say "+team[i]->query("name")+"���յĻ��ڴ����Ѿ����꣬�����˰ɡ�");
				return 1;
			}
		}
		if (me == team[i]) continue;
		if (!interactive(team[i])) {
			command("say "+team[i]->query("name")+"���ڲ����ߣ����������˰ɡ�");
			return 1;
		}
	}
	maxexp=minexp=team[0]->query("combat_exp");
	maxplayer=team[0];
	for (i=0;i<sizeof(team);i++){

		if (!ultrap(team[i])) {
			command("say ����·;Σ�գ��ҿ���λ"+RANK_D->query_respect(me)+"����Ŭ�������ճ�Ϊ��ѧ����ʦ��");
			return 1;
		}

		if (team[i]->query("combat_exp") < 500000) {
			command("say ����·;Σ�գ��ҿ���λ"+RANK_D->query_respect(me)+"��Ҫһ���ô��");
			return 1;
		}
		if (team[i]->query("balance") < 1000000 && !wizardp(team[i])) {
			command("say ������Σ�յ��£��ҿ�"+team[i]->query("name")+RANK_D->query_respect(team[i])+"û���⳥������");
			return 1;
		}
		if (team[i]->query_condition("job_busy") && !wizardp(team[i])){
			command("say һֱ���ں�����ģ��ҿ���λ"+team[i]->query("name")+RANK_D->query_respect(team[i])+"����ȥЪϢƬ�̰ɣ�");
			return 1;
		}
		totalexp = totalexp + team[i]->query("combat_exp");
		if(team[i]->query("combat_exp") > maxexp) {
			maxexp=team[i]->query("combat_exp");
			maxplayer=team[i];
		}
		else if(team[i]->query("combat_exp") < minexp)
			minexp=team[i]->query("combat_exp");
	}
	if( totalexp < 1000000 ){
		command("say ����·;Σ�գ��ҿ���λ�ƺ��޴�����������");
		return 1;
	}

	if( totalexp < 20000000 && (maxexp-minexp) > 5000000 ){
		command("say ����·;Σ�գ���Ҫ����Эͬ��ս���ҿ���λ��ʵ��������⣬����������Ӱɡ�");
		return 1;
	}


	teams=sizeof(team);

// ѡ����Ŀ��

	if(!objectp(place = find_object(target_list[random(sizeof(target_list))])))
		place = load_object(target_list[random(sizeof(target_list))]);
	if (!place) {
		command("say ��ʱû������Ҫ�ͼ�"+RANK_D->query_respect(team[0])+"����");
		return 1;
	}

	target = new(__DIR__"hbtarget");
	target->move(place);

	for (i=0; i<5; i++)
		target->random_move();

	place = environment(target);

 	if ( place->query("outdoors"))
		endname =  MAP_D->query_map_short(place->query("outdoors"))+place->query("short");
 	else if ( place->query("indoors"))
		endname =  MAP_D->query_map_short(place->query("indoors"))+place->query("short");
	else endname =  place->query("short");

	command("say �뻤����һ��������"+endname+CYN"��"+target->name()+"���С�");

	log_file("job/hubiao",
		sprintf("%8s%-10s������������õ��������񣬹�%1s��������Ҫ�ʹ�"HIR"%s"NOR"��\n",
			me->name(1),
			"("+capitalize(me->query("id"))+")",
			chinese_number(sizeof(team)),
			endname
		), me
	);

	message_vision("$N������Ѻ��"+chinese_number(sizeof(team)*50)+"���ƽ𽻸����ھ֡�\n", me);

	say("һ���ڳ�����Ժʻ����\n");

	cart=new(__DIR__"obj/cart");
	cart->set_temp("teams", teams);

	if(teams > 3)
		cart->set_temp("team4",team[3]);
	if(teams > 2)
		cart->set_temp("team3",team[2]);
	if(teams > 1)
		cart->set_temp("team2",team[1]);
	if(teams > 0)
		cart->set_temp("team1",team[0]);

	cart->set("long", cart->query("long")+"��֧�����ɸ����ھ���ʦ"+me->query("name")+"�����͵�"+HIR+endname+HIY+target->name()+NOR"���ϵġ�\n");
	cart->set("teamhead", me->query("name"));
	cart->set("arrive", endname);
	cart->set("target", target);

	for(i=0; i < sizeof(team); i++) {
		team[i]->set("day_jobs/hubiao/last_time",time());
		team[i]->add("day_jobs/hubiao/times",1);
		team[i]->set_temp("protecting",cart);
		team[i]->apply_condition("job_busy", 45);
		team[i]->add("balance", -500000);
		team[i]->set_temp("death", team[i]->query("death_count"));
		//GIFT_D->check_count(team[i],this_object(),"����");
	}

	cart->move(environment());

	biaotou = new(__DIR__"biaotou");
	biaotou->set("qi", maxplayer->query("max_qi"));
	biaotou->set("eff_qi", maxplayer->query("max_qi"));
	biaotou->set("max_qi", maxplayer->query("max_qi"));
	biaotou->set("jing", maxplayer->query("max_jing"));
	biaotou->set("max_jing", maxplayer->query("max_jing"));
	biaotou->set("neili", maxplayer->query("max_neili"));
	biaotou->set("max_neili", maxplayer->query("max_neili"));
	biaotou->set("jingli", maxplayer->query("max_jingli"));
	biaotou->set("max_jingli", maxplayer->query("max_jingli"));
	biaotou->move(environment());
	biaotou->set_temp("protecting",cart);
	biaotou->set("combat_exp", maxplayer->query("combat_exp"));
	NPC_D->init_npc_skill(biaotou,NPC_D->check_level(biaotou));
	ob=new("/clone/money/silver");
	ob->set_amount(1000+random(100));
	ob->set("name","����");
	ob->move(cart);
/*
	ob=new(__DIR__"biaoshi");
	ob->move(environment());
	ob->set_temp("protecting", cart);

	ob=new(__DIR__"biaoshi");
	ob->move(environment());
	ob->set_temp("protecting", cart);
*/
	me->set_temp("hubiao/where", base_name(environment(target))); //����Ŀ��
	me->set_temp("hubiao/biao_time", uptime());
	me->set_temp("hubiao/target", target);
	return 1;
}

int test_dart()
{
	object ob = this_player();

	if (ob->query_condition("job_busy")
	 || ob->query_temp("protecting")
	 || random(100) > 80) {
		command("say ����û������Ҫ�ͼ�"+RANK_D->query_respect(ob)+"����");
		return 1;
	}

	command("say ���Ǹ����ھ��������У��б�������Ҫ�͵�������");
	do_accept("quest");
	return 1;
}
